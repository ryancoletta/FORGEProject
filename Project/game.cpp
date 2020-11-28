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
	_turn(0)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	gameLoop();
}

void Game::gameLoop() {
	Graphics graphics;
	SpriteManager spriteManager(&graphics);
	Input input;
	SDL_Event event;

	_level = new Level(&graphics, "Assets/level1.tmx", &_entityManager, &spriteManager);

	Entity* playerEntity = _entityManager.GetPlayerEntity();
	if (!playerEntity) { return; }


	int lastUpdateTimeMs = SDL_GetTicks();
	while (true) {
		input.beginNewFrame();

		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.repeat == 0) {
					input.keyDownEvent(event);
				}
			}
			else if (event.type == SDL_KEYUP) {
				input.keyUpEvent(event);
			}
			if (event.type == SDL_QUIT) {
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
}
void Game::draw(Graphics& graphics) {
	graphics.clear();

	_level->draw();
	_entityManager.draw();

	graphics.render();
}
void Game::update(int deltaTime) {
	_entityManager.update(deltaTime);
}

Game::~Game() {
	delete _level;
}
