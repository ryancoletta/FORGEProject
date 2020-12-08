#pragma once
#include <map>
#include "globals.h"
#include <string>

class Sprite;
class Graphics;
class AnimationManager;

class SpriteManager
{
public:
	SpriteManager(Graphics* graphics, AnimationManager* animationManager);
	~SpriteManager();
	Sprite* loadSprite(int spriteID, const std::string& filePath, Vector2 sourcePosition, Vector2 sourceScale);
private:
	Graphics* _graphics;
	AnimationManager* _animationManager;
	std::multimap<int,Sprite*> _loadedSprites;
};

