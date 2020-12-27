#include "globals.h"
#include "sprite.h"
#include "graphics.h"

Sprite::Sprite(Graphics* graphics, const std::string& filePath, Vector2 sourcePosition, Vector2 sourceScale, Vector2 origin) :
	_graphics(graphics),
	_origin(origin)
{
	_spriteSheet = SDL_CreateTextureFromSurface(graphics->getRenderer(), graphics->loadImage(filePath));
	if (_spriteSheet == NULL) { printf("Error: unable to load image\n"); }

	// TODO wrapping behaviour whenever the source position is invalid, kinda weird, maybe refactor
	int w, h;
	SDL_QueryTexture(_spriteSheet, NULL, NULL, &w, &h);
	while (sourcePosition.x + sourceScale.x > w ||
		sourcePosition.y + sourceScale.y > h) {
		sourcePosition.x -= w;
		sourcePosition.y += sourceScale.y;
	}

	_sourceRect.x = sourcePosition.x;
	_sourceRect.y = sourcePosition.y;
	_sourceRect.w = sourceScale.x;
	_sourceRect.h = sourceScale.y;
}

SDL_Rect Sprite::getSourceRect() { return _sourceRect; }

void Sprite::draw(Vector2 position, int clockWiseAngleRotation) {
	SDL_Rect destRect = { 
		position.x - _origin.x,
		position.y - _origin.y,
		_sourceRect.w * globals::SPRITE_SCALE, 
		_sourceRect.h * globals::SPRITE_SCALE 
	};
	_graphics->blitSurface(_spriteSheet, &_sourceRect, &destRect, clockWiseAngleRotation);
}