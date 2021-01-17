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
#include "SpriteInstance.h"

Game::Game() :
	_nextLevelEvent(SDL_RegisterEvents(1)),
	_turn(0)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	_graphics = DBG_NEW Graphics();
	_entityManager = DBG_NEW EntityManager();
	_animationManager = DBG_NEW AnimationManager();
	_spriteManager = DBG_NEW SpriteManager(_graphics, _animationManager);
	_levelManager = DBG_NEW LevelManager(_nextLevelEvent);
	_input = DBG_NEW Input();
	_hudManager = DBG_NEW HudManager(_graphics);
}

Game::~Game() {
	delete _graphics;
	delete _entityManager;
	delete _spriteManager;
	delete _levelManager;
	delete _input;
	delete _hudManager;

	_graphics = NULL;
	_entityManager = NULL;
	_spriteManager = NULL;
	_levelManager = NULL;
	_input = NULL;
	_hudManager = NULL;
}

void Game::play() {	

	// load the next level
	while (_levelManager->loadNextLevel(_graphics, _entityManager, _spriteManager)) {
		// find the player
		Entity* playerEntity = _entityManager->GetPlayerEntity();
		if (!playerEntity) { return; }

		// main loop
		int lastUpdateTimeMs = SDL_GetTicks();
		bool levelComplete = false;
		while (!levelComplete) {
			_input->beginNewFrame();

			if (SDL_PollEvent(&_event)) {
				if (_event.type == SDL_KEYDOWN) {
					if (_event.key.repeat == 0) {
						_input->keyDownEvent(_event);
					}
				}
				else if (_event.type == SDL_KEYUP) {
					_input->keyUpEvent(_event);
				}
				if (_event.type == _nextLevelEvent) {
					levelComplete = true;
				}
				if (_event.type == SDL_QUIT) {
					return;
				}
			}
			if (_input->isKeyDown(SDL_SCANCODE_ESCAPE)) {
				return;
			}
			else if (_input->isKeyDown(SDL_SCANCODE_UP)) {
				if (playerEntity->move(_turn, Vector2::down())) { _turn++; }
			}
			else if (_input->isKeyDown(SDL_SCANCODE_RIGHT)) {
				if (playerEntity->move(_turn, Vector2::right())) { _turn++; }
			}
			else if (_input->isKeyDown(SDL_SCANCODE_DOWN)) {
				if (playerEntity->move(_turn, Vector2::up())) { _turn++; }
			}
			else if (_input->isKeyDown(SDL_SCANCODE_LEFT)) {
				if (playerEntity->move(_turn, Vector2::left())) { _turn++; }
			}
			else if (_input->isKeyDown(SDL_SCANCODE_Z)) {
				if (_turn > 0) { _entityManager->undoAll(--_turn); }
			}
			else if (_input->isKeyDown(SDL_SCANCODE_R)) {
				if (_turn != 0) {
					_entityManager->resetAll();
					_turn = 0;
				}
			}

			int currentUpdateTimeMs = SDL_GetTicks();
			int elaspedUpdateTimeMs = currentUpdateTimeMs - lastUpdateTimeMs;
			lastUpdateTimeMs = currentUpdateTimeMs;
			update(std::min(elaspedUpdateTimeMs, globals::MAX_FRAME_TIME));

			draw();
		}
		
		// pause, victorious
		SDL_Delay(500);
		SDL_PumpEvents();
		SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);

		// reset
		_turn = 0;
		_entityManager->clearEntities();
	}
}

void Game::draw() {
	_graphics->clear();

	_levelManager->draw();
	_entityManager->draw();
	_hudManager->draw();

	_graphics->render();
}

void Game::update(int deltaTime) {
	_entityManager->update(deltaTime);
}
