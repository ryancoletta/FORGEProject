#include "entitymanager.h"
#include "entity.h"
#include "level.h"
#include "sprite.h"
#include "tile.h"

void EntityManager::addEntity(int entityID, Level* level, Sprite* sprite, Tile* startTile) {
	Entity* newEntity = new Entity(entityID, level, sprite, startTile);
	_allEntities.push_back(newEntity);
}
void EntityManager::draw() {
	for (int i = 0; i < _allEntities.size(); i++) {
		_allEntities[i]->draw();
	}
}
void EntityManager::update(int deltaTime) {
	for (int i = 0; i < _allEntities.size(); i++) {
		_allEntities[i]->update(deltaTime);
	}
}
Entity* EntityManager::GetEntitiesByType(int entityID) {
	for (int i = 0; i < _allEntities.size(); i++) {
		if (_allEntities[i]->getEntityID() == entityID) {
			return _allEntities[i];
		}
	}
	return NULL;
}
EntityManager::~EntityManager() {
	for (int i = 0; i < _allEntities.size(); i++) {
		delete _allEntities[i];
	}
}