#include "levelmanager.h"
#include <SDL.h>
#include "graphics.h"
#include "entitymanager.h"
#include "spritemanager.h"
#include "level.h"

LevelManager::LevelManager(Uint32 nextLevelEvent) :
	_currentLevel(NULL),
	_levelIndex(-1),
	_nextLevelEvent(nextLevelEvent)
{}
LevelManager::~LevelManager() {
	clear();
}

bool LevelManager::loadLevel(int levelIndex, Graphics* graphics, EntityManager* entityManager, SpriteManager* spriteManager) {
	if (levelIndex >= _levelPaths.size()) { return false; }

	_levelIndex = levelIndex;
	if (_currentLevel != NULL) {
		clear();
	}
	_currentLevel = DBG_NEW Level(this, graphics, &_levelPaths[_levelIndex], entityManager, spriteManager);
	return true;
}

bool LevelManager::loadNextLevel(Graphics* graphics, EntityManager* entityManager, SpriteManager* spriteManager) {
	return loadLevel(_levelIndex + 1, graphics, entityManager, spriteManager);
}

void LevelManager::levelComplete() {
	SDL_Event nextLevelEvent;
	nextLevelEvent.type = _nextLevelEvent;
	SDL_PushEvent(&nextLevelEvent);
}

void LevelManager::draw() {
	_currentLevel->draw();
}

void LevelManager::clear() {
	delete _currentLevel;
	_currentLevel = NULL;
}