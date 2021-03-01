#include "globals.h"
#include <SDL.h>
#include <algorithm>
#include "game.h"
#include "input.h"
#include "globals.h"
#include "Sprites/animatedsprite.h"
#include "Sprites/animation.h"
#include "Sprites/spritemanager.h"
#include "level.h"
#include "Entities/entity.h"
#include "Sprites/animationmanager.h"
#include "levelmanager.h"
#include "HUD/hudmanager.h"
#include "Sprites/sprite.h"
#include "HUD/text.h"
#include <cmath>
#include "Entities/playerentity.h"

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
	_background			= _spriteManager->loadSprite("background", "Assets/background.png", "Assets/tile_palette_NES.png", "Shaders/base.vert", "Shaders/base.frag", Vector2::zero(), Vector2(globals::WINDOW_WIDTH, globals::WINDOW_HEIGHT));
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

void Game::BaseState::Enter() {
	_fade = 0.0f;
	_stateComplete = false;
	_stateEnterTimeMS = SDL_GetTicks();
}

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

	// fade in and out
	if (!_stateComplete && _fade < 1.0f) {
		_fade += deltaTimeMs / globals::MAX_SPRITE_FADE_TIME;
		_owner->_spriteManager->updateAllSpriteFade(std::min(_fade, 0.99f));
		return;
	}
	else if (_stateComplete && _fade > 0.0f) {
		_fade -= deltaTimeMs / globals::MAX_SPRITE_FADE_TIME;
		_owner->_spriteManager->updateAllSpriteFade(std::max(std::min(_fade, 0.99f), 0.0f));
		return;
	}
}

// ----------------------------------------------------------------------------------------------------------
// Title State
Game::TitleState::TitleState(Game* owner) : BaseState(owner)
{}

void Game::TitleState::Enter() {
	BaseState::Enter();
	_startText = _owner->_hudManager->writeText("PUSH SPACE BUTTON", Vector2(globals::WINDOW_WIDTH / 2.0f, globals::WINDOW_HEIGHT / 2.0f + 125.0f), MIDDLE_ALIGNED);
	_creditText = _owner->_hudManager->writeText("@RyGuyDev", Vector2(globals::WINDOW_WIDTH / 2.0f, globals::WINDOW_HEIGHT / 2.0f + 200.0f), MIDDLE_ALIGNED);
	_owner->_hudManager->spawnImage("title_sprite", "Assets/logo.png", "Assets/tile_palette_NES.png", "Shaders/base.vert", "Shaders/base.frag", Vector2::zero(), Vector2(globals::WINDOW_WIDTH, globals::WINDOW_HEIGHT), Vector2(globals::WINDOW_WIDTH / 2, globals::WINDOW_HEIGHT / 2));
}

void Game::TitleState::Execute(int deltaTimeMs)
{
	BaseState::Execute(deltaTimeMs);
	
	if (_stateComplete && _fade <= 0.0f) {
		_owner->_stateMachine->ChangeState(_owner->_levelState);
		return;
	}
	else {
		if (_owner->_input->isKeyDown(SDL_SCANCODE_SPACE)) {
			_stateComplete = true;
		}

		// flash text
		if (!_stateComplete) {
			float timeSinceEntry = SDL_GetTicks() - _stateEnterTimeMS;
			bool isVisible = floor(std::fmod(timeSinceEntry / 300, 2)) == 0.0f;
			_startText->setVisibility(isVisible);
			//_startText->setOffset(Vector2(0, 10 * sin(_timer / 100.0f)));
		}
		else { _startText->setVisibility(true); }
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
	BaseState::Enter();
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

		_helpText = _owner->_hudManager->writeText("Z to undo | R to reset", Vector2(globals::WINDOW_WIDTH / 2.0f, 50.0f), MIDDLE_ALIGNED);
		_helpText->setVisibility(false);
		_lastInputTimeMS = _stateEnterTimeMS;
	}
}

void Game::LevelState::Execute(int deltaTimeMs)
{
	BaseState::Execute(deltaTimeMs);

	if (_stateComplete && _fade <= 0.0f) {
		_owner->_stateMachine->ChangeState(_owner->_levelState);
		return;
	}
	else if (_fade >= 1.0f) {
		// check for a next level event
		if (_event.type == _owner->_nextLevelEvent) {
			_stateComplete = true;
		}

		if (_owner->_input->anyKeyDown()) {
			_owner->_entityManager->sortEntities();

			_lastInputTimeMS = SDL_GetTicks();
			_helpText->setVisibility(false);
		}
		else {
			// only display help text if player hasn't input for a few seconds
			float timeSinceEntry = SDL_GetTicks() - _lastInputTimeMS;
			if (timeSinceEntry > globals::MAX_TIME_TILL_HELP_TEXT_DISPLAYED && _turn > 0) {
				_helpText->setVisibility(true);
			}
		}

		// undo and reset
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
		// dead players cannot access the below
		else if (!_playerEntity->isAlive()) {
			return;
		}
		// handle movement
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
}

void Game::LevelState::Exit()
{
	_owner->_entityManager->clearEntities();
	_owner->_hudManager->clearScreen();
}