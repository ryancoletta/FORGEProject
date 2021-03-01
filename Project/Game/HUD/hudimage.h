#pragma once
#include "globals.h"

class Sprite;

class HudImage
{
public:
	HudImage(Sprite* sprite, Vector2 position);
	void draw();
private:
	Sprite* _sprite;
	Vector2 _position;
};

