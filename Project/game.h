#pragma once
#include "graphics.h"
#include "entity.h"
#include "entityManager.h"
#include "level.h"
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

