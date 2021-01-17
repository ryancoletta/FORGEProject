#pragma once
#include "globals.h"
#include <SDL.h>

class Graphics;
class Material;

class Sprite
{
public:
	Sprite(Graphics* graphics, Material* material, Vector2 origin = Vector2::zero());
	virtual ~Sprite() {}

	Material* getMaterial();

	virtual void update(int deltaTime) {};
	virtual void draw(Vector2 position, const float clockWiseAngleRotation = 0.0f);

protected:
	Graphics* _graphics;
	Material* _material;
	Vector2 _origin;
};

