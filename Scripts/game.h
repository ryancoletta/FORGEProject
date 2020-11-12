#pragma once
#include "graphics.h"
#include "sprite.h"

class Game {
public:
	Game();
	~Game();
private:
	const int FPS = 60;
	const int MAX_FRAME_TIME = 5 * 1000 / FPS;
	void gameLoop();
	void draw(Graphics &graphics);
	void update(float deltaTime);

	Sprite _player;
};

