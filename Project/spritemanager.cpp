#include "spritemanager.h"
#include "animatedsprite.h"
#include "sprite.h"
#include "animation.h"
#include "graphics.h"
#include "entity.h"

SpriteManager::SpriteManager() :
	_graphics(NULL)
{}
SpriteManager::SpriteManager(Graphics* graphics) :
	_graphics(graphics)
{}
Sprite* SpriteManager::loadSprite(int spriteID, const std::string& filePath, Vector2 sourcePosition, Vector2 sourceScale) {
	Sprite* newSprite;
	switch (spriteID) {
		case static_cast<int>(ENTITY_PLAYER) : {
			newSprite = new AnimatedSprite(_graphics, filePath, Vector2(0, 0), Vector2(16, 16));
			Animation* playerIdle = new Animation("player_idle", 2, 500, Vector2(0, 0), Vector2(16, 16));
			static_cast<AnimatedSprite*>(newSprite)->addAnimation(playerIdle);
			static_cast<AnimatedSprite*>(newSprite)->playAnimation("player_idle", true);
			break;
		}
		case static_cast<int>(ENTITY_CHICKEN) : {
			newSprite = new AnimatedSprite(_graphics, filePath, Vector2(48, 0), Vector2(16, 16));
			Animation* chickenIdle = new Animation("chicken_idle", 2, 500, Vector2(48, 0), Vector2(16, 16));
			static_cast<AnimatedSprite*>(newSprite)->addAnimation(chickenIdle);
			static_cast<AnimatedSprite*>(newSprite)->playAnimation("chicken_idle", true);
			break;
		}
		default: {
			// these sprites all are uniform (no branching animations) so theres no need to create individual instances
			if (_loadedSprites.count(spriteID) == 0) {
				newSprite = new Sprite(_graphics, filePath, sourcePosition, sourceScale);
			}
			else { return _loadedSprites.find(spriteID)->second; }
		}
	}

	_loadedSprites.insert(std::pair<int, Sprite*>(spriteID, newSprite));
	return newSprite;
}

SpriteManager::~SpriteManager() {

	std::multimap<int, Sprite*>::iterator it;
	for (it = _loadedSprites.begin(); it != _loadedSprites.end(); it++)
	{
		delete it->second;
	}
	_loadedSprites.clear();
}
