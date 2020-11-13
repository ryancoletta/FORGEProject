#pragma once
#include "graphics.h"
#include "entity.h"
#include "grid.h"

class Game {
public:
	Game();
private:
	void gameLoop();
	void draw(Graphics &graphics);
	void update(int deltaTime);

	Grid _grid;
	Entity _playerEntity;
};

