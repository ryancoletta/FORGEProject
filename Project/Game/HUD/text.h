#pragma once
#include "globals.h"
#include <string>
#include <vector>
#include <SDL.h>


class Sprite;
class Font;

enum TextAlignment {
	LEFT_ALIGNED,
	MIDDLE_ALIGNED,
	RIGHT_ALIGNED,
};

class Text
{
public:
	Text(Font* font, std::string text, glm::vec2 position, TextAlignment alignment = LEFT_ALIGNED);

	glm::vec2 getOrigin();

	void setOffset(glm::vec2 offset);
	void setVisibility(bool isVisible);

	void draw();

private:
	bool _isVisible;
	glm::vec2 _offset;
	SDL_Rect _rect;
	std::vector<Sprite*> _charSprites;
	TextAlignment _alignment;
};

