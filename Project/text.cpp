#include "text.h"
#include "font.h"
#include "sprite.h"
#include "spriteinstance.h"
#include "material.h"

Text::Text(Font* font, std::string text, Vector2 position, TextAlignment alignment)
{
	for (int i = 0; i < text.length(); i++) {
		_charSprites.push_back(font->getCharSprite(text[i]));
	}

	SDL_Rect charRect = _charSprites[0]->getMaterial()->getSourceRect();

	_rect.x = position.x;
	_rect.y = position.y;
	_rect.w = _charSprites.size() * charRect.w * globals::SPRITE_SCALE;
	_rect.h = charRect.h;

	switch (alignment) {
		case MIDDLE_ALIGNED:
			_rect.x -= _rect.w / 2;
			break;
		case RIGHT_ALIGNED:
			_rect.x -= _rect.w;
			break;
	}
}

void Text::draw() {
	if (_charSprites.empty()) { return; }

	for (int i = 0; i < _charSprites.size(); i++) {
		_charSprites[i]->draw(Vector2(_rect.x, _rect.y) + Vector2(8 * i, 0) * globals::SPRITE_SCALE);
	}
}