#include "levelmanager.h"
#include <SDL.h>
#include "Graphics/graphics.h"
#include "Entities/entitymanager.h"
#include "Sprites/spritemanager.h"
#include "level.h"

LevelManager::LevelManager(Uint32 nextLevelEvent) :
	_currentLevel(nullptr),
	_levelIndex(-1),
	_nextLevelEvent(nextLevelEvent)
{}
LevelManager::~LevelManager() {
	clear();
}

int LevelManager::getLevelIndex()
{
	return _levelIndex;
}

void LevelManager::update(int deltaTimeMs)
{
	if (_currentLevel) {
		_currentLevel->update(deltaTimeMs);
	}
}

bool LevelManager::loadLevel(int levelIndex, Graphics* graphics, EntityManager* entityManager, SpriteManager* spriteManager) {
	if (levelIndex >= _levelPaths.size()) { return false; }

	_levelIndex = levelIndex;
	if (_currentLevel != nullptr) {
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
	if (_currentLevel) {
		_currentLevel->draw();
	}
}

void LevelManager::undo(int turn)
{
	if (_currentLevel) {
		_currentLevel->undo(turn);
	}
}

void LevelManager::reset()
{
	if (_currentLevel) {
		_currentLevel->reset();
	}
}

void LevelManager::clear() {
	delete _currentLevel;
	_currentLevel = nullptr;
}