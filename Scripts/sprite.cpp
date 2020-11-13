#include "sprite.h"
#include "globals.h"

Sprite::Sprite() : _graphics(NULL), _spriteSheet(NULL), _sourceRect({ 0,0,0,0 }), _position(Vector2::zero()) {  }
Sprite::Sprite(Graphics* graphics, const std::string& filePath, Vector2 sourcePosition, Vector2 sourceScale, Vector2 position) : _graphics(graphics), _position(position)
{
	_sourceRect.x = sourcePosition.x;
	_sourceRect.y = sourcePosition.y;
	_sourceRect.w = sourceScale.x;
	_sourceRect.h = sourceScale.y;

	_spriteSheet = SDL_CreateTextureFromSurface(graphics->getRenderer(), graphics->loadImage(filePath));
	if (_spriteSheet == NULL) { printf("Error: unable to load image\n"); }
}
void Sprite::draw() {
	SDL_Rect destRect = { 
		_position.x,
		_position.y,
		_sourceRect.w * globals::SPRITE_SCALE, 
		_sourceRect.h * globals::SPRITE_SCALE 
	};
	_graphics->blitSurface(_spriteSheet, &_sourceRect, &destRect);
}

void Sprite::setPosition(Vector2 position) { _position = position; }