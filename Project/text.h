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
	Text(Font* font, std::string text, Vector2 position, TextAlignment alignment = LEFT_ALIGNED);

	Vector2 getOrigin();

	void setOffset(Vector2 offset);
	void setVisibility(bool isVisible);

	void draw();

private:
	bool _isVisible;
	Vector2 _offset;
	SDL_Rect _rect;
	std::vector<Sprite*> _charSprites;
	TextAlignment _alignment;
};

