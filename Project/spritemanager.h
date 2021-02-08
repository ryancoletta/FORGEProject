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

	Sprite* loadSprite(std::string spriteName, const std::string& texturePath, const std::string& palettePath, const std::string& vertexPath, const std::string& fragmentPath, Vector2 sourcePosition, Vector2 sourceScale);
	Sprite* loadSprite(GidElement gid, const std::string& filePath, const std::string& vertexPath, const std::string& fragmentPath, Vector2 sourcePosition, Vector2 sourceScale);

	void updateAllSpriteFade(float newFade);

private:
	Graphics* _graphics;
	AnimationManager* _animationManager;
	std::multimap<std::string, Sprite*> _loadedSprites;
	float _fade;
};

