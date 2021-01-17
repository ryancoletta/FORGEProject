#pragma once
#include <map>
#include "globals.h"
#include <string>

class SpriteInstance;
class Graphics;
class AnimationManager;
enum GidElement;

class SpriteManager
{
public:
	SpriteManager(Graphics* graphics, AnimationManager* animationManager);
	~SpriteManager();

	SpriteInstance* loadSprite(GidElement gid, const std::string& filePath, Vector2 sourcePosition, Vector2 sourceScale);

private:
	Graphics* _graphics;
	AnimationManager* _animationManager;
	std::multimap<int, SpriteInstance*> _loadedSprites;
};

