#include "globals.h"
#include <SDL.h>
#include <algorithm>
#include "game.h"
#include "input.h"
#include "globals.h"
#include "animatedsprite.h"
#include "animation.h"
#include "spritemanager.h"
#include "level.h"
#include "entity.h"
#include "animationmanager.h"
#include "levelmanager.h"
#include "hudmanager.h"
#include "sprite.h"
#include "text.h"
#include <cmath>
#include "playerentity.h"

Game::Game() :
	_nextLevelEvent(SDL_RegisterEvents(1)),
	_gameOver(false)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	_graphics			= DBG_NEW Graphics();
	_entityManager		= DBG_NEW EntityManager();
	_animationManager	= DBG_NEW AnimationManager();
	_spriteManager		= DBG_NEW SpriteManager(_graphics, _animationManager);
	_levelManager		= DBG_NEW LevelManager(_nextLevelEvent);
	_input				= DBG_NEW Input();
	_hudManager			= DBG_NEW HudManager(_graphics, _spriteManager);
	_stateMachine		= DBG_NEW StateMachine();
	_background			= _spriteManager->loadSprite("background", "Assets/background.png", "Assets/tile_palette_NES.png", "base.vert", "base.frag", Vector2::zero(), Vector2(globals::WINDOW_WIDTH, globals::WINDOW_HEIGHT));
	_titleState			= DBG_NEW TitleState(this);
	_levelState			= DBG_NEW LevelState(this);
}

Game::~Game() {
	delete _graphics;
	delete _entityManager;
	delete _spriteManager;
	delete _levelManager;
	delete _input;
	delete _hudManager;
	delete _stateMachine;
	delete _titleState;
	delete _levelState;

	_graphics			= nullptr;
	_entityManager		= nullptr;
	_spriteManager		= nullptr;
	_levelManager		= nullptr;
	_input				= nullptr;
	_hudManager			= nullptr;
	_stateMachine		= nullptr;
}

void Game::play() {
	_stateMachine->ChangeState(_titleState);

	int lastUpdateTimeMs = SDL_GetTicks();
	while (!_gameOver) {
		int currentUpdateTimeMs = SDL_GetTicks();
		int elaspedUpdateTimeMs = currentUpdateTimeMs - lastUpdateTimeMs;
		lastUpdateTimeMs = currentUpdateTimeMs;
		_stateMachine->ExecuteStateUpdate(elaspedUpdateTimeMs);
		update(std::min(elaspedUpdateTimeMs, globals::MAX_FRAME_TIME));

		draw();
	}
}

void Game::draw() {
	_graphics->clear();
	_graphics->begin();

	_background->draw(Vector2(0,0));
	_levelManager->draw();
	_entityManager->draw();
	_hudManager->draw();

	_graphics->render();
}

void Game::update(int deltaTime) {
	_entityManager->update(deltaTime);
	_levelManager->update(deltaTime);
}



// ----------------------------------------------------------------------------------------------------------
// Base State
Game::BaseState::BaseState(Game* owner) : _owner(owner)
{}

void Game::BaseState::Execute(int deltaTimeMs)
{
	_owner->_input->beginNewFrame();
	if (SDL_PollEvent(&_event)) {
		if (_event.type == SDL_KEYDOWN) {
			if (_event.key.repeat == 0) {
				_owner->_input->keyDownEvent(_event);
			}
		}
		else if (_event.type == SDL_KEYUP) {
			_owner->_input->keyUpEvent(_event);
		}
		if (_event.type == SDL_QUIT) {
			_owner->_gameOver = true;
		}
	}
	if (_owner->_input->isKeyDown(SDL_SCANCODE_ESCAPE)) {
		_owner->_gameOver = true;
	}
}

// ----------------------------------------------------------------------------------------------------------
// Title State
Game::TitleState::TitleState(Game* owner) : BaseState(owner)
{}

void Game::TitleState::Enter() {
	_timer = 0;
	_startText = _owner->_hudManager->writeText("press SPACE to start", Vector2(globals::WINDOW_WIDTH / 2.0f, globals::WINDOW_HEIGHT / 2.0f + 200.0f), MIDDLE_ALIGNED);	
	_owner->_hudManager->spawnImage("title_sprite", "Assets/logo.png", "Assets/tile_palette_NES.png", "base.vert", "base.frag", Vector2::zero(), Vector2(globals::WINDOW_WIDTH, globals::WINDOW_HEIGHT), Vector2(globals::WINDOW_WIDTH / 2, globals::WINDOW_HEIGHT / 2));
}

void Game::TitleState::Execute(int deltaTimeMs)
{
	BaseState::Execute(deltaTimeMs);
	
	_timer += deltaTimeMs;
	bool visible = floor(std::fmod(_timer / 300, 2)) == 0.0f;
	_startText->setVisibility(visible);
	//_startText->setOffset(Vector2(0, 10 * sin(_timer / 100.0f)));

	if (_owner->_input->isKeyDown(SDL_SCANCODE_SPACE)) {
		TitleState::_owner->_stateMachine->ChangeState(_owner->_levelState);
	}
}

void Game::TitleState::Exit() {
	_owner->_hudManager->clearScreen();
}

// ----------------------------------------------------------------------------------------------------------
// Level State
Game::LevelState::LevelState(Game* owner) : BaseState(owner)
{}

void Game::LevelState::Enter()
{
	_fade = 0.0f;
	_levelComplete = false;
	_turn = 0;
	if (!_owner->_levelManager->loadNextLevel(_owner->_graphics, _owner->_entityManager, _owner->_spriteManager)) {
		printf("No more levels remain");
		_owner->_gameOver = true;
	}
	else {
		// find the player
		Entity* playerEntity = _owner->_entityManager->GetPlayerEntity();
		if (!playerEntity) {
			_owner->_gameOver = true;
		}
		else {
			_playerEntity = static_cast<PlayerEntity*>(playerEntity);
		}

		// display the level number
		int levelNumber = _owner->_levelManager->getLevelIndex() + 1;
		_owner->_hudManager->writeText("Level " + std::to_string(levelNumber), Vector2(globals::WINDOW_WIDTH - 30.0f, globals::WINDOW_HEIGHT - 30.0f), RIGHT_ALIGNED);
	}
}

void Game::LevelState::Execute(int deltaTimeMs)
{
	BaseState::Execute(deltaTimeMs);

	// fade in and out
	if (!_levelComplete && _fade < 1.0f) {
		_fade += deltaTimeMs / _maxFadeMs;
		return;
	}
	else if (_levelComplete && _fade > 0.0f) {
		_fade -= deltaTimeMs / _maxFadeMs;
		return;
	}
	else if (_levelComplete) {
		_owner->_stateMachine->ChangeState(_owner->_levelState);
		return;
	}

	// look for a next level event
	if (_event.type == _owner->_nextLevelEvent) {
		_levelComplete = true;
	}

	if (_owner->_input->anyKeyDown()) {
		_owner->_entityManager->sortEntities();
	}

	// handle player input
	if (_owner->_input->isKeyDown(SDL_SCANCODE_Z)) {
		if (_turn > 0) { 
			_turn--;
			_owner->_entityManager->undoAll(_turn);
			_owner->_levelManager->undo(_turn);
		}
	}
	else if (_owner->_input->isKeyDown(SDL_SCANCODE_R)) {
		if (_turn != 0) {
			_owner->_entityManager->resetAll();
			_owner->_levelManager->reset();
			_turn = 0;
		}
	}
	// only undo availible to dead players
	else if (!_playerEntity->isAlive()) {
		return;
	}
	else if (_owner->_input->isKeyDown(SDL_SCANCODE_UP)) {
		if (_playerEntity->move(_turn, Vector2::down())) { _turn++; }
	}
	else if (_owner->_input->isKeyDown(SDL_SCANCODE_RIGHT)) {
		if (_playerEntity->move(_turn, Vector2::right())) { _turn++; }
	}
	else if (_owner->_input->isKeyDown(SDL_SCANCODE_DOWN)) {
		if (_playerEntity->move(_turn, Vector2::up())) { _turn++; }
	}
	else if (_owner->_input->isKeyDown(SDL_SCANCODE_LEFT)) {
		if (_playerEntity->move(_turn, Vector2::left())) { _turn++; }
	}
}

void Game::LevelState::Exit()
{
	_owner->_entityManager->clearEntities();
	_owner->_hudManager->clearScreen();
}