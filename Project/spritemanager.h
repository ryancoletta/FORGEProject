#pragma once
#include <map>
#include "globals.h"
#include <string>

class Sprite;
class Graphics;
class AnimationManager;
enum GidElement;

class SpriteManager
{
public:
	SpriteManager(Graphics* graphics, AnimationManager* animationManager);
	~SpriteManager();

	Sprite* loadSprite(GidElement gid, const std::string& filePath, const std::string& vertexPath, const std::string& fragmentPath, Vector2 sourcePosition, Vector2 sourceScale);

private:
	Graphics* _graphics;
	AnimationManager* _animationManager;
	std::multimap<int, Sprite*> _loadedSprites;
};

