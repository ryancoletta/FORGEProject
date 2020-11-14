#include "game.h"

#include <SDL.h>
#include "input.h"
#include "globals.h"
#include "animatedsprite.h"

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	gameLoop();
}
void Game::gameLoop() {
	Graphics graphics;
	Input input;
	SDL_Event event;

	// TODO map is based on a tilemap
	Sprite test(&graphics, "Assets/spritesheet.png", Vector2(2 * 16, 0), Vector2(16, 16));
	_level = Level(10, 10, &test);

	// TODO spawn entities by reading a tilemap (including the player entity)
	AnimatedSprite animatedPlayerSprite(&graphics, "Assets/spritesheet.png", Vector2(0, 0), Vector2(16, 16));
	Animation playerIdle("player_idle", 2, 500, Vector2(0,0), Vector2(16, 16));
	animatedPlayerSprite.addAnimation(playerIdle);
	animatedPlayerSprite.playAnimation("player_idle", true);
	_playerEntity = Entity(&_level, &animatedPlayerSprite, _level.getTile(0,0));

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
			_playerEntity.move(Vector2::down());
		}
		else if (input.isKeyDown(SDL_SCANCODE_RIGHT)) {
			_playerEntity.move(Vector2::right());
		}
		else if (input.isKeyDown(SDL_SCANCODE_DOWN)) {
			_playerEntity.move(Vector2::up());
		}
		else if (input.isKeyDown(SDL_SCANCODE_LEFT)) {
			_playerEntity.move(Vector2::left());
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

	_level.draw();
	_playerEntity.draw();

	graphics.render();
}
void Game::update(int deltaTime) {
	_playerEntity.update(deltaTime);
}
