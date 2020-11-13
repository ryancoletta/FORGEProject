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

	// TODO change the animated sprite class to accept an ANIMATION rather than require setupAnimations
	AnimatedSprite animatedPlayerSprite(&graphics, "Assets/spritesheet.png", Vector2(1 * 16, 16), Vector2(16, 16), 500);
	animatedPlayerSprite.setupAnimations();
	animatedPlayerSprite.playAnimation("Test", true);

	_grid = Grid(10, 10);
	_playerEntity = Entity(&_grid, &animatedPlayerSprite, _grid.getTile(0,0));

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

	_playerEntity.draw(); // this is using SPRITE not ANIMATEDSPRITE, why?

	graphics.render();
}
void Game::update(int deltaTime) {
	_playerEntity.update(deltaTime);
}
