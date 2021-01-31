#include "hudimage.h"
#include "sprite.h"

HudImage::HudImage(Sprite* sprite, Vector2 position) :
	_sprite(sprite),
	_position(position)
{}

void HudImage::draw()
{
	_sprite->draw(_position);
}
