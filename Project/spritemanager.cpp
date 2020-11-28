#include "spritemanager.h"
#include "animatedsprite.h"
#include "sprite.h"
#include "animation.h"
#include "graphics.h"
#include "entity.h"

SpriteManager::SpriteManager(Graphics* graphics) :
	_graphics(graphics)
{}
Sprite* SpriteManager::loadSprite(int spriteID, const std::string& filePath, Vector2 sourcePosition, Vector2 sourceScale) {
	if (_loadedSprites.count(spriteID) == 0) {
		Sprite* newSprite;

		// set up all animations for each specific entity
		switch (spriteID) {
			case static_cast<int>(ENTITY_PLAYER) : {
				newSprite = new AnimatedSprite(_graphics, "Assets/spritesheet.png", Vector2(0, 0), Vector2(16, 16));
				Animation* playerIdle = new Animation("player_idle", 2, 500, Vector2(0, 0), Vector2(16, 16));
				static_cast<AnimatedSprite*>(newSprite)->addAnimation(playerIdle);
				static_cast<AnimatedSprite*>(newSprite)->playAnimation("player_idle", true);
				break;
			}
			default: {
				newSprite = new Sprite(_graphics, filePath, sourcePosition, sourceScale);
				break;
			}
		}

		_loadedSprites.insert(std::pair<int, Sprite*>(spriteID, newSprite));
	}
	return _loadedSprites[spriteID];
}

SpriteManager::~SpriteManager() {
	for (int i = 0; i < _loadedSprites.size(); i++) {
		delete _loadedSprites[i];
	}
}
