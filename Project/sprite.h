#pragma once
#include <string>
#include <SDL.h>
#include "globals.h"

class Graphics;

class Sprite
{
public:
	Sprite();
	Sprite(Graphics* graphics, const std::string& filePath, Vector2 sourcePosition, Vector2 sourceScale);
	~Sprite();
	virtual void update(int deltaTime) {};
	virtual void draw(Vector2 position);

protected:
	Graphics* _graphics;
	SDL_Rect _sourceRect;
	SDL_Texture* _spriteSheet;
};

