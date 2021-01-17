#include "spriteinstance.h"
#include "graphics.h"
#include "material.h"

SpriteInstance::SpriteInstance(Graphics* graphics, Material* material, Vector2 screenPosition) :
	_graphics(graphics),
	_material(material),
	_position(screenPosition)
{
}

void SpriteInstance::draw(Vector2 position, int clockWiseAngleRotation)
{
	_graphics->draw(_material, position);
}

Material* SpriteInstance::getMaterial()
{
	return _material;
}
