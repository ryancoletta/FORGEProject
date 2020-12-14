#include "globals.h"
#include "spritemanager.h"
#include "animatedsprite.h"
#include "sprite.h"
#include "animation.h"
#include "graphics.h"
#include "entity.h"
#include "animationmanager.h"
#include "level.h"

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

Sprite* SpriteManager::loadSprite(GidElement gid, const std::string& filePath, Vector2 sourcePosition, Vector2 sourceScale) {
	Sprite* newSprite = NULL;
	if (gid == GID_ENTITY_PLAYER_UP || gid == GID_ENTITY_PLAYER_RIGHT || gid == GID_ENTITY_PLAYER_DOWN || gid == GID_ENTITY_PLAYER_LEFT) {
		switch (gid) {
			case GID_ENTITY_PLAYER_UP:
				newSprite = DBG_NEW AnimatedSprite(_graphics, filePath, Vector2(0, 0), Vector2(48, 48), Vector2(48, 48));
				break;
			case GID_ENTITY_PLAYER_RIGHT:
				newSprite = DBG_NEW AnimatedSprite(_graphics, filePath, Vector2(48, 0), Vector2(48, 48), Vector2(48, 48));
				break;
			case GID_ENTITY_PLAYER_DOWN:
				newSprite = DBG_NEW AnimatedSprite(_graphics, filePath, Vector2(96, 0), Vector2(48, 48), Vector2(48, 48));
				break;
			case GID_ENTITY_PLAYER_LEFT:
				newSprite = DBG_NEW AnimatedSprite(_graphics, filePath, Vector2(144, 0), Vector2(48, 48), Vector2(48, 48));
				break;
		}
		Animation* up = _animationManager->loadAnimation("up", 1, 500, Vector2(0, 0), Vector2(48, 48));
		Animation* right = _animationManager->loadAnimation("right", 1, 500, Vector2(48, 0), Vector2(48, 48));
		Animation* down = _animationManager->loadAnimation("down", 1, 500, Vector2(96, 0), Vector2(48, 48));
		Animation* left = _animationManager->loadAnimation("left", 1, 500, Vector2(144, 0), Vector2(48, 48));
		static_cast<AnimatedSprite*>(newSprite)->addAnimation(up);
		static_cast<AnimatedSprite*>(newSprite)->addAnimation(right);
		static_cast<AnimatedSprite*>(newSprite)->addAnimation(down);
		static_cast<AnimatedSprite*>(newSprite)->addAnimation(left);
	}
	else if (gid == GID_ENTITY_CHICKEN) {
		newSprite = DBG_NEW AnimatedSprite(_graphics, filePath, Vector2(48, 0), sourceScale);
		Animation* newAnimation = _animationManager->loadAnimation("chicken_idle", 2, 500, Vector2(48, 0), Vector2(16, 16));
		static_cast<AnimatedSprite*>(newSprite)->addAnimation(newAnimation);
		static_cast<AnimatedSprite*>(newSprite)->playAnimation("chicken_idle", true);
	}
	// these sprites all are uniform (no branching animations) so theres no need to create individual instances
	else if (_loadedSprites.count(gid) == 0) {
		newSprite = DBG_NEW Sprite(_graphics, filePath, sourcePosition, sourceScale);
	}
	else { 
		return _loadedSprites.find(gid)->second; 
	}

	if (newSprite) {
		_loadedSprites.insert(std::pair<int, Sprite*>(gid, newSprite));
	}
	return newSprite;
}


