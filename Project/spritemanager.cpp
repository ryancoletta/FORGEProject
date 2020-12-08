#include "globals.h"
#include "spritemanager.h"
#include "animatedsprite.h"
#include "sprite.h"
#include "animation.h"
#include "graphics.h"
#include "entity.h"
#include "animationmanager.h"

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

Sprite* SpriteManager::loadSprite(int spriteID, const std::string& filePath, Vector2 sourcePosition, Vector2 sourceScale) {
	Sprite* newSprite;
	switch (spriteID) {
		case static_cast<int>(ENTITY_PLAYER) : {
			// animation instance class that is unique and defines speed and offset
			newSprite = DBG_NEW AnimatedSprite(_graphics, filePath, Vector2(0, 0), Vector2(16, 16));
			Animation* newAnimation = _animationManager->loadAnimation("player_idle", 2, 500, Vector2(0, 0), Vector2(16, 16));
			static_cast<AnimatedSprite*>(newSprite)->addAnimation(newAnimation);
			static_cast<AnimatedSprite*>(newSprite)->playAnimation("player_idle", true);
			break;
		}
		case static_cast<int>(ENTITY_CHICKEN) : {
			newSprite = DBG_NEW AnimatedSprite(_graphics, filePath, Vector2(48, 0), Vector2(16, 16));
			Animation* newAnimation = _animationManager->loadAnimation("chicken_idle", 2, 500, Vector2(48, 0), Vector2(16, 16));
			static_cast<AnimatedSprite*>(newSprite)->addAnimation(newAnimation);
			static_cast<AnimatedSprite*>(newSprite)->playAnimation("chicken_idle", true);
			break;
		}
		default: {
			// these sprites all are uniform (no branching animations) so theres no need to create individual instances
			if (_loadedSprites.count(spriteID) == 0) {
				newSprite = DBG_NEW Sprite(_graphics, filePath, sourcePosition, sourceScale);
			}
			else { return _loadedSprites.find(spriteID)->second; }
		}
	}

	if (newSprite != NULL) {
		_loadedSprites.insert(std::pair<int, Sprite*>(spriteID, newSprite));
	}
	return newSprite;
}


