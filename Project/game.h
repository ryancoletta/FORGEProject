#pragma once
#include "graphics.h"
#include "entityManager.h"

class Game {
public:
	Game();
	~Game();
private:
	void gameLoop();
	void draw(Graphics &graphics);
	void update(int deltaTime);

	int _turn;
	Level* _level;
	EntityManager _entityManager;
};

