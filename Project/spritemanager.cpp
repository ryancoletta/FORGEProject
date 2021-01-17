#include "globals.h"
#include "spritemanager.h"
#include "animatedsprite.h"
#include "animation.h"
#include "graphics.h"
#include "entity.h"
#include "animationmanager.h"
#include "level.h"
#include "material.h"
#include "spriteinstance.h"

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
	Material* newMaterial = _graphics->loadMaterial(filePath, "test.vert", "test.frag", sourcePosition, sourceScale);

	if (gid == GID_ENTITY_PLAYER) {
		newSprite = DBG_NEW Sprite(_graphics, newMaterial, Vector2(48, 48));
	}
	else if (gid == GID_ENTITY_CHICKEN) {
		newSprite = DBG_NEW AnimatedSprite(_graphics, newMaterial);
		Animation* newAnimation = _animationManager->loadAnimation("chicken_idle", 2, 500, Vector2(48, 0), Vector2(16, 16));
		static_cast<AnimatedSprite*>(newSprite)->addAnimation(newAnimation);
		static_cast<AnimatedSprite*>(newSprite)->playAnimation("chicken_idle", true);
	}
	// these sprites all are uniform (no branching animations) so theres no need to create individual instances
	else if (_loadedSprites.count(gid) == 0) {
		newSprite = DBG_NEW Sprite(_graphics, newMaterial);
	}
	else { 
		return _loadedSprites.find(gid)->second; // gids which should be rotated are NOT, instead using the non rotated sprite
	}

	if (newSprite) {
		_loadedSprites.insert(std::pair<int, Sprite*>(gid, newSprite));
	}
	return newSprite;
}


