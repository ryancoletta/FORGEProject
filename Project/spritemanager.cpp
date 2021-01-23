#include "globals.h"
#include "spritemanager.h"
#include "animatedsprite.h"
#include "animation.h"
#include "graphics.h"
#include "entity.h"
#include "animationmanager.h"
#include "level.h"
#include "sprite.h"

SpriteManager::SpriteManager(Graphics* graphics, AnimationManager* animationManager) :
	_graphics(graphics),
	_animationManager(animationManager)
{}

SpriteManager::~SpriteManager() {

	std::multimap<int, Sprite*>::iterator it;
	for (it = _loadedSprites.begin(); it != _loadedSprites.end(); it++)
	{
		delete it->second;
	}
	_loadedSprites.clear();

	delete _animationManager;
}

// TODO eww, I hate all of this
Sprite* SpriteManager::loadSprite(GidElement gid, const std::string& texturePath, const std::string& vertexPath, const std::string& fragmentPath, Vector2 sourcePosition, Vector2 sourceScale) {
	Sprite* newSprite = NULL;
	if (gid == GID_ENTITY_PLAYER) {
		Vector2 entityScale = Vector2(48, 48);
		//newSprite = DBG_NEW Sprite(_graphics, texturePath, vertexPath, fragmentPath, sourcePosition - Vector2(16,16), entityScale);

		
		newSprite = DBG_NEW AnimatedSprite(_graphics, texturePath, vertexPath, fragmentPath, sourcePosition - Vector2(16, 16), entityScale, glm::vec2(0,-8));
		Animation* newAnimation = _animationManager->loadAnimation("player_down", 4, 100, sourcePosition - Vector2(16, 16), entityScale);
		static_cast<AnimatedSprite*>(newSprite)->addAnimation(newAnimation);
		static_cast<AnimatedSprite*>(newSprite)->playAnimation("player_down", true);

		newAnimation = _animationManager->loadAnimation("player_left", 4, 100, sourcePosition - Vector2(16, 16) + Vector2(64 * 3, 0), entityScale);
		static_cast<AnimatedSprite*>(newSprite)->addAnimation(newAnimation);

		newAnimation = _animationManager->loadAnimation("player_up", 4, 100, sourcePosition - Vector2(16, 16) + Vector2(64 * 6, 0), entityScale);
		static_cast<AnimatedSprite*>(newSprite)->addAnimation(newAnimation);

		newAnimation = _animationManager->loadAnimation("player_right", 4, 100, sourcePosition - Vector2(16, 16) + Vector2(64 * 9, 0), entityScale);
		static_cast<AnimatedSprite*>(newSprite)->addAnimation(newAnimation);
	}
	else if (gid == GID_ENTITY_BOX) {
		Vector2 entityScale = Vector2(16, 32);
		newSprite = DBG_NEW Sprite(_graphics, texturePath, vertexPath, fragmentPath, sourcePosition, entityScale, glm::vec2(0, -24));
	}
	else if (_loadedSprites.count(gid) == 0) {
		newSprite = DBG_NEW Sprite(_graphics, texturePath, vertexPath, fragmentPath, sourcePosition, sourceScale);
	}
	else { 
		return _loadedSprites.find(gid)->second;
	}

	if (newSprite) {
		_loadedSprites.insert(std::pair<int, Sprite*>(gid, newSprite));
	}
	return newSprite;
}


