#pragma once
#include "graphics.h"
#include "entityManager.h"

class Game {
public:
	Game();
	~Game();
	void nextLevel();
private:
	void gameLoop();
	void draw(Graphics &graphics);
	void update(int deltaTime);

	SDL_Event _event;
	int _turn;
	int _level;
	Uint32 _nextLevelEvent;
	Level* _currentLevel;
	EntityManager _entityManager;
};

