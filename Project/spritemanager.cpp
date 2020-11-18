#include "spritemanager.h"
#include "sprite.h"
#include "graphics.h"


Sprite* SpriteManager::loadSprite(int spriteID, Graphics* graphics, const std::string& filePath, Vector2 sourcePosition, Vector2 sourceScale) {
	
	if (_loadedSprites.count(spriteID) == 0) {
		Sprite* newSprite = new Sprite(graphics, filePath, sourcePosition, sourceScale);
		_loadedSprites.insert(std::pair<int, Sprite*>(spriteID, newSprite));
	}
	return _loadedSprites[spriteID];
}

SpriteManager::~SpriteManager() {
	for (int i = 0; i < _loadedSprites.size(); i++) {
		delete _loadedSprites[i];
	}
}
