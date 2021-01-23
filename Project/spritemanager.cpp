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
		newSprite = DBG_NEW Sprite(_graphics, texturePath, vertexPath, fragmentPath, sourcePosition - Vector2(16, 16), Vector2(48, 48));
	}
	else if (gid == GID_ENTITY_CHICKEN) {
		newSprite = DBG_NEW AnimatedSprite(_graphics, texturePath, vertexPath, fragmentPath, sourcePosition, sourceScale);
		Animation* newAnimation = _animationManager->loadAnimation("chicken_idle", 2, 500, sourcePosition, sourceScale);
		static_cast<AnimatedSprite*>(newSprite)->addAnimation(newAnimation);
		static_cast<AnimatedSprite*>(newSprite)->playAnimation("chicken_idle", true);
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


