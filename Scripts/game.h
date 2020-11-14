#pragma once
#include "graphics.h"
#include "entity.h"
#include "level.h"
class Game {
public:
	Game();
private:
	void gameLoop();
	void draw(Graphics &graphics);
	void update(int deltaTime);

	Level _level;
	Entity _playerEntity;
};

