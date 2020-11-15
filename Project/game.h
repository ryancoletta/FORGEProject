#pragma once
#include "graphics.h"
#include "level.h"
#include "entityManager.h"
#include "entity.h"

class Game {
public:
	Game();
private:
	void gameLoop();
	void draw(Graphics &graphics);
	void update(int deltaTime);

	Level _level;
	EntityManager _entityManager;
	Entity _playerEntity;
};

