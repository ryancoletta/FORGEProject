#pragma once
#include "globals.h"
#include <map>
#include <string>

class SpriteInstance;
class Graphics;

class Font
{
public:
	Font(Graphics* graphics, const std::string& filePath, Vector2 charSize);
	~Font();

	SpriteInstance* getCharSprite(char c);
private:
	std::map<char, SpriteInstance*> _fontMap;
};

