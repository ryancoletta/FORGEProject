#pragma once
#include "graphics.h"
#include "globals.h"

class Sprite
{
public:
	Sprite();
	Sprite(Graphics* graphics, const std::string& filePath, Vector2 sourcePosition, Vector2 sourceScale, Vector2 position = Vector2::zero());
	virtual void update(int deltaTime) {};
	virtual void draw();
	void setPosition(Vector2 position);
protected:
	Graphics* _graphics;
	SDL_Rect _sourceRect;
	SDL_Texture* _spriteSheet;
	Vector2 _position;
};

