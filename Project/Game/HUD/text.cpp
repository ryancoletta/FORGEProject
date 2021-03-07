#include "text.h"
#include "font.h"
#include "Sprites/sprite.h"

Text::Text(Font* font, std::string text, glm::vec2 position, TextAlignment alignment) :
	_alignment(alignment),
	_offset(glm::vec2(0)),
	_isVisible(true)
{
	for (int i = 0; i < text.length(); i++) {
		_charSprites.push_back(font->getCharSprite(text[i]));
	}

	SDL_Rect charRect = _charSprites[0]->getSourceRect();

	_rect.x = static_cast<int>(position.x);
	_rect.y = static_cast<int>(position.y);
	_rect.w = _charSprites.size() * charRect.w * globals::SPRITE_SCALE;
	_rect.h = charRect.h;

	switch (_alignment) {
	case MIDDLE_ALIGNED:
		_rect.x -= _rect.w / 2.0f - charRect.w / 2.0f * globals::SPRITE_SCALE;
		break;
	case RIGHT_ALIGNED:
		_rect.x -= _rect.w - charRect.w * globals::SPRITE_SCALE;
		break;
	}
}

glm::vec2 Text::getOrigin()
{
	switch (_alignment) {
	case MIDDLE_ALIGNED:
		return glm::vec2(_rect.x + _rect.w / 2, _rect.y);
	case RIGHT_ALIGNED:
		return glm::vec2(_rect.x + _rect.w, _rect.y);
	}

	return glm::vec2(_rect.x, _rect.y);
}

void Text::setOffset(glm::vec2 offset)
{
	_offset = offset;
}

void Text::setVisibility(bool isVisible)
{
	_isVisible = isVisible;
}

void Text::draw() {
	if (_charSprites.empty() || !_isVisible) { return; }

	for (int i = 0; i < _charSprites.size(); i++) {
		_charSprites[i]->draw(glm::vec2(_rect.x + _offset.x, _rect.y + _offset.y) + glm::vec2(8 * i * globals::SPRITE_SCALE, 0));
	}
}