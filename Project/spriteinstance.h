#pragma once
#include "globals.h"
#include <SDL.h>

class Graphics;
class Material;

class SpriteInstance
{
public:
	SpriteInstance(Graphics* graphics, Material* material);
	virtual void update(int deltaTime) {};
	virtual void draw(Vector2 position, int clockWiseAngleRotation = 0);

	Material* getMaterial();
private:
	Graphics* _graphics;
	Vector2 _position;
	Material* _material;
};

