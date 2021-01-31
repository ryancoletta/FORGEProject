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

	std::multimap<std::string, Sprite*>::iterator it;
	for (it = _loadedSprites.begin(); it != _loadedSprites.end(); it++)
	{
		delete it->second;
	}
	_loadedSprites.clear();

	delete _animationManager;
}

Sprite* SpriteManager::loadSprite(std::string spriteName, const std::string& texturePath, const std::string& vertexPath, const std::string& fragmentPath, Vector2 sourcePosition, Vector2 sourceScale)
{
	if (_loadedSprites.count(spriteName) == 0) {
		Sprite* newSprite = DBG_NEW Sprite(_graphics, texturePath, vertexPath, fragmentPath, sourcePosition, sourceScale);
		_loadedSprites.insert(std::pair<std::string, Sprite*>(spriteName, newSprite));
		return newSprite;
	}
	else return _loadedSprites.find(spriteName)->second;
}

// TODO find a better way
Sprite* SpriteManager::loadSprite(GidElement gid, const std::string& texturePath, const std::string& vertexPath, const std::string& fragmentPath, Vector2 sourcePosition, Vector2 sourceScale) {
	std::string spriteName = "GID NO. " + std::to_string((int)gid);
	
	Sprite* newSprite = nullptr;
	if (gid == GID_ENTITY_PLAYER) {
		Vector2 entityScale = Vector2(48, 48);
		newSprite = DBG_NEW AnimatedSprite(_graphics, texturePath, vertexPath, fragmentPath, sourcePosition - Vector2(16, 16), entityScale, glm::vec2(0,-6));
		Animation* newAnimation = _animationManager->loadAnimation("player_down", 4, 100, sourcePosition - Vector2(16, 16), entityScale);
		static_cast<AnimatedSprite*>(newSprite)->addAnimation(newAnimation);
		static_cast<AnimatedSprite*>(newSprite)->playAnimation("player_down", true);

		newAnimation = _animationManager->loadAnimation("player_left", 4, 100, sourcePosition - Vector2(16, 16) + Vector2(64 * 3, 0), entityScale);
		static_cast<AnimatedSprite*>(newSprite)->addAnimation(newAnimation);

		newAnimation = _animationManager->loadAnimation("player_up", 4, 100, sourcePosition - Vector2(16, 16) + Vector2(64 * 6, 0), entityScale);
		static_cast<AnimatedSprite*>(newSprite)->addAnimation(newAnimation);

		newAnimation = _animationManager->loadAnimation("player_right", 4, 100, sourcePosition - Vector2(16, 16) + Vector2(64 * 9, 0), entityScale);
		static_cast<AnimatedSprite*>(newSprite)->addAnimation(newAnimation);

		newAnimation = _animationManager->loadAnimation("player_death", 9, 60, sourcePosition - Vector2(16, 16) + Vector2(64 * 12, 0), entityScale);
		static_cast<AnimatedSprite*>(newSprite)->addAnimation(newAnimation);
	}
	else if (gid == GID_ENTITY_BOX) {
		Vector2 entityScale = Vector2(16, 32);
		newSprite = DBG_NEW AnimatedSprite(_graphics, texturePath, vertexPath, fragmentPath, sourcePosition, entityScale, glm::vec2(0, -27));
		Animation* newAnimation = _animationManager->loadAnimation("box_fall", 6, 50, sourcePosition, entityScale);
		static_cast<AnimatedSprite*>(newSprite)->addAnimation(newAnimation);
	}
	else if (gid == GID_ENTITY_BAT) {
		newSprite = DBG_NEW AnimatedSprite(_graphics, texturePath, vertexPath, fragmentPath, sourcePosition, sourceScale, glm::vec2(3, -9));
		Animation* newAnimation = _animationManager->loadAnimation("goon_idle", 5, 100, sourcePosition, sourceScale);
		static_cast<AnimatedSprite*>(newSprite)->addAnimation(newAnimation);
		static_cast<AnimatedSprite*>(newSprite)->playAnimation("goon_idle", true);
	}
	else if (gid == GID_TILE_SPIKE_OFF || gid == GID_TILE_SPIKE_ON) {
		newSprite = DBG_NEW AnimatedSprite(_graphics, texturePath, vertexPath, fragmentPath, sourcePosition, sourceScale);

		sourcePosition -= Vector2((gid - GID_TILE_SPIKE_OFF) * 16, 0); // TODO if its the ON spike, then the animation needs to look backward, improve this
		Animation* newAnimation = _animationManager->loadAnimation("spikes_on", 4, 100, sourcePosition, sourceScale);
		static_cast<AnimatedSprite*>(newSprite)->addAnimation(newAnimation);
	}
	else if (_loadedSprites.count(spriteName) == 0) {
		newSprite = DBG_NEW Sprite(_graphics, texturePath, vertexPath, fragmentPath, sourcePosition, sourceScale);
	}
	else { 
		return _loadedSprites.find(spriteName)->second;
	}

	if (newSprite) {
		_loadedSprites.insert(std::pair<std::string, Sprite*>(spriteName, newSprite));
	}
	return newSprite;
}


