#pragma once
#include "globals.h"
#include <map>
#include <string>

class Sprite;
class Graphics;

class Font
{
public:
	Font(Graphics* graphics, const std::string& filePath, Vector2 charSize);
	~Font();

	Sprite* getCharSprite(char c);
private:
	std::map<char, Sprite*> _fontMap;
};

