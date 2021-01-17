#include "spriteinstance.h"
#include "graphics.h"
#include "material.h"

SpriteInstance::SpriteInstance(Graphics* graphics, Material* material, Vector2 origin) :
	_graphics(graphics),
	_material(material),
	_origin(origin)
{}

void SpriteInstance::draw(Vector2 position, const float clockWiseAngleRotation)
{
	SDL_Rect destRect = {
		position.x,
		position.y,
		_material->getSourceRect().w * globals::SPRITE_SCALE,
		_material->getSourceRect().h * globals::SPRITE_SCALE
	};
	_graphics->draw(_material, _material->getSourceRect(), destRect, clockWiseAngleRotation);
}

Material* SpriteInstance::getMaterial()
{
	return _material;
}
