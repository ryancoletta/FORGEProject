#pragma once
#include <map>
#include "globals.h"
#include <string>

class Sprite;
class Graphics;

class SpriteManager
{
public:
	~SpriteManager();
	Sprite* loadSprite(int spriteID, Graphics* graphics, const std::string& filePath, Vector2 sourcePosition, Vector2 sourceScale);
private:
	std::map<int,Sprite*> _loadedSprites;
};

