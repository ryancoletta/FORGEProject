#include "globals.h"
#include "sprite.h"
#include "graphics.h"

Sprite::Sprite(Graphics* graphics, const std::string& filePath, Vector2 sourcePosition, Vector2 sourceScale) : 
	_graphics(graphics)
{
	_sourceRect.x = sourcePosition.x;
	_sourceRect.y = sourcePosition.y;
	_sourceRect.w = sourceScale.x;
	_sourceRect.h = sourceScale.y;

	_spriteSheet = SDL_CreateTextureFromSurface(graphics->getRenderer(), graphics->loadImage(filePath));
	if (_spriteSheet == NULL) { printf("Error: unable to load image\n"); }
}
void Sprite::draw(Vector2 position) {
	SDL_Rect destRect = { 
		position.x,
		position.y,
		_sourceRect.w * globals::SPRITE_SCALE, 
		_sourceRect.h * globals::SPRITE_SCALE 
	};
	_graphics->blitSurface(_spriteSheet, &_sourceRect, &destRect);
}