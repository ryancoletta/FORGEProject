#pragma once
#include <map>
#include "globals.h"
#include <string>

class Sprite;
class Graphics;

class SpriteManager
{
public:
	SpriteManager(Graphics* graphics);
	~SpriteManager();
	Sprite* loadSprite(int spriteID, const std::string& filePath, Vector2 sourcePosition, Vector2 sourceScale);
private:
	Graphics* _graphics;
	std::map<int,Sprite*> _loadedSprites;
};

