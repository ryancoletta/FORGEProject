#include "game.h"

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "input.h"

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	gameLoop();
}
Game::~Game() {

}
void Game::gameLoop() {
	Graphics graphics;
	Input input;
	SDL_Event event;

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

		if (input.isKeyDown(SDL_SCANCODE_ESCAPE) == true) {
			return;
		}

		int currentUpdateTimeMs = SDL_GetTicks();
		int elaspedUpdateTimeMs = currentUpdateTimeMs - lastUpdateTimeMs;
		lastUpdateTimeMs = currentUpdateTimeMs;
		update(std::min(elaspedUpdateTimeMs, MAX_FRAME_TIME));
	}
}
void Game::draw(Graphics& graphics) {

}
void Game::update(float deltaTime) {

}
