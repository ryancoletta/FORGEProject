#pragma once
#include "globals.h"

class Sprite;

class HudImage
{
public:
	HudImage(Sprite* sprite, glm::vec2 position);
	void draw();
private:
	Sprite* _sprite;
	glm::vec2 _position;
};

