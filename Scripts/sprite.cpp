#include "sprite.h"
#include "globals.h"

Sprite::Sprite() {}
Sprite::Sprite(Graphics& graphics, const std::string& filePath, int sourceX, int sourceY, int width, int height, float posX, float posY) :
	_x(posX), _y(posY)  {
	_sourceRect.x = sourceX;
	_sourceRect.y = sourceY;
	_sourceRect.w = width;
	_sourceRect.h = height;

	_spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));
	if (_spriteSheet == NULL) { printf("Error: unable to load image\n"); }
}
Sprite::~Sprite() {
}
void Sprite::update() {

}
void Sprite::draw(Graphics& graphics, int x, int y) {
	SDL_Rect destRect = { 
		x, 
		y, 
		_sourceRect.w * globals::SPRITE_SCALE, 
		_sourceRect.h * globals::SPRITE_SCALE 
	};
	graphics.blitSurface(_spriteSheet, &_sourceRect, &destRect);
}