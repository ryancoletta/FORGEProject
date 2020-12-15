#pragma once
#include <string>
#include <SDL.h>
#include "globals.h"

class Graphics;

class Sprite
{
public:
	Sprite(Graphics* graphics, const std::string& filePath, Vector2 sourcePosition, Vector2 sourceScale, Vector2 origin = Vector2::zero());
	virtual ~Sprite() {}

	virtual void update(int deltaTime) {};
	virtual void draw(Vector2 position, int clockWiseAngleRotation = 0);

protected:
	Vector2 _origin;
	Graphics* _graphics;
	SDL_Rect _sourceRect;
	SDL_Texture* _spriteSheet;
};

