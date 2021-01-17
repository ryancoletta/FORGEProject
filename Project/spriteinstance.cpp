#include "spriteinstance.h"
#include "graphics.h"
#include "material.h"

SpriteInstance::SpriteInstance(Graphics* graphics, Material* material) :
	_graphics(graphics),
	_material(material),
	_position(Vector2::zero())
{
}

void SpriteInstance::draw(Vector2 position, int clockWiseAngleRotation)
{
	SDL_Rect destRect = {
		position.x,
		position.y,
		_material->getSourceRect().w * globals::SPRITE_SCALE,
		_material->getSourceRect().h * globals::SPRITE_SCALE
	};
	_graphics->draw(_material, destRect);
}

Material* SpriteInstance::getMaterial()
{
	return _material;
}
