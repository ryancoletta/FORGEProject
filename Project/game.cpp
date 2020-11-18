#include <SDL.h>
#include "game.h"
#include "input.h"
#include "globals.h"
#include "animatedsprite.h"
#include "animation.h"
#include "spritemanager.h"
#include "level.h"
#include "entity.h"

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	gameLoop();
}

void Game::gameLoop() {
	Graphics graphics;
	SpriteManager spriteManager;
	Input input;
	SDL_Event event;


	// TODO bug where, if this isn't new, then when the pointer gets passed around, it doesn't always work??? (in entity)
	_level = new Level(&graphics, "Assets/level1.tmx", &_entityManager, &spriteManager);

	// temp spawn the player here
	/*
	AnimatedSprite animatedPlayerSprite(&graphics, "Assets/spritesheet.png", Vector2(0, 0), Vector2(16, 16));
	Animation playerIdle("player_idle", 2, 500, Vector2(0,0), Vector2(16, 16));
	animatedPlayerSprite.addAnimation(playerIdle);
	animatedPlayerSprite.playAnimation("player_idle", true);
	*/

	Entity* playerEntity = _entityManager.GetEntitiesByType(0);
	


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
			playerEntity->move(Vector2::down());
		}
		else if (input.isKeyDown(SDL_SCANCODE_RIGHT)) {
			playerEntity->move(Vector2::right());
		}
		else if (input.isKeyDown(SDL_SCANCODE_DOWN)) {
			playerEntity->move(Vector2::up());
		}
		else if (input.isKeyDown(SDL_SCANCODE_LEFT)) {
			playerEntity->move(Vector2::left());
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
