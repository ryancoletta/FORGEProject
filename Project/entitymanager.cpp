#include "entitymanager.h"
#include "entity.h"

void EntityManager::addEntity(Entity* entity) {
	_allEntities.push_back(entity);
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