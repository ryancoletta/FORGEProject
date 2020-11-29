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

Game::Game() :
	_nextLevelEvent(SDL_RegisterEvents(1)),
	_turn(0)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	gameLoop();
}

void Game::nextLevel() {
	// TODO mem alloc error
	//_level++; 
	// TODO temp loop thru all levels
	_level = (_level + 1) % 3;
	SDL_Event nextLevelEvent;
	nextLevelEvent.type = _nextLevelEvent;
	SDL_PushEvent(&nextLevelEvent);
}

void Game::gameLoop() {
	Graphics graphics;
	SpriteManager spriteManager(&graphics);
	Input input;

	std::string allLevels[] = { 
		"Assets/level1.tmx",
		"Assets/level2.tmx",
		"Assets/level3.tmx",
	};

	while (_level < allLevels->size()) {
		// load the level
		_currentLevel = new Level(this, &graphics, allLevels[_level], &_entityManager, &spriteManager);

		// find the player
		Entity* playerEntity = _entityManager.GetPlayerEntity();
		if (!playerEntity) { return; }

		// play the level
		int lastUpdateTimeMs = SDL_GetTicks();
		bool complete = false;
		while (!complete) {
			input.beginNewFrame();

			if (SDL_PollEvent(&_event)) {
				if (_event.type == SDL_KEYDOWN) {
					if (_event.key.repeat == 0) {
						input.keyDownEvent(_event);
					}
				}
				else if (_event.type == SDL_KEYUP) {
					input.keyUpEvent(_event);
				}
				if (_event.type == _nextLevelEvent) {
					complete = true;
				}
				if (_event.type == SDL_QUIT) {
					return;
				}
			}

			if (input.isKeyDown(SDL_SCANCODE_ESCAPE)) {
				return;
			}
			else if (input.isKeyDown(SDL_SCANCODE_UP)) {
				if (playerEntity->move(_turn, Vector2::down())) { _turn++; }
			}
			else if (input.isKeyDown(SDL_SCANCODE_RIGHT)) {
				if (playerEntity->move(_turn, Vector2::right())) { _turn++; }
			}
			else if (input.isKeyDown(SDL_SCANCODE_DOWN)) {
				if (playerEntity->move(_turn, Vector2::up())) { _turn++; }
			}
			else if (input.isKeyDown(SDL_SCANCODE_LEFT)) {
				if (playerEntity->move(_turn, Vector2::left())) { _turn++; }
			}
			else if (input.isKeyDown(SDL_SCANCODE_Z)) {
				if (_turn > 0) { _entityManager.undoAll(--_turn); }
			}
			else if (input.isKeyDown(SDL_SCANCODE_R)) {
				if (_turn != 0) {
					_entityManager.resetAll();
					_turn = 0;
				}
			}

			int currentUpdateTimeMs = SDL_GetTicks();
			int elaspedUpdateTimeMs = currentUpdateTimeMs - lastUpdateTimeMs;
			lastUpdateTimeMs = currentUpdateTimeMs;
			update(std::min(elaspedUpdateTimeMs, globals::MAX_FRAME_TIME));

			draw(graphics);
		}

		// TODO hacky alternative to palette swapping for an exit transition
		graphics.setMaxColor(200, 200, 255);
		draw(graphics);
		SDL_Delay(500);
		graphics.setMaxColor(100, 100, 200);
		draw(graphics);
		SDL_Delay(500);
		graphics.setMaxColor(50, 50, 150);
		draw(graphics);
		SDL_Delay(500);
		graphics.setMaxColor(0, 0, 0);
		draw(graphics);
		SDL_Delay(500);
		graphics.setMaxColor(255, 255, 255);
		
		//SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT); // TODO you can queue up a bunch of moves during this delay, want to prevent

		// reset data
		_turn = 0;
		_entityManager.clearEntities();
		delete _currentLevel;
	}
}
void Game::draw(Graphics& graphics) {
	graphics.clear();

	_currentLevel->draw();
	_entityManager.draw();

	graphics.render();
}
void Game::update(int deltaTime) {
	_entityManager.update(deltaTime);
}

Game::~Game() {}
