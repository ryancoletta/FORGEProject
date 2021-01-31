#include "globals.h"
#include "entitymanager.h"
#include "entity.h"
#include "level.h"
#include "sprite.h"
#include "tile.h"
#include "playerentity.h"
#include "directionalentity.h"
#include "boxentity.h"
#include "batentity.h"

EntityManager::~EntityManager() { clearEntities(); }

std::vector<Entity*> EntityManager::GetEntitiesByType(EntityType entityID) {

	std::vector<Entity*> allEntitiesOfType;
	for (int i = 0; i < _allEntities.size(); i++)
	{
		if (_allEntities[i]->getEntityType() == entityID) {
			allEntitiesOfType.push_back(_allEntities[i]);
		}
	}
	return allEntitiesOfType;
}

Entity* EntityManager::GetPlayerEntity() {
	std::vector<Entity*> playerEntities = GetEntitiesByType(ENTITY_PLAYER);
	if (playerEntities.empty()) {
		printf("Error: no player found in level\n");
		return NULL;
	}
	return playerEntities[0];
}

void EntityManager::addEntity(GidElement gid, Level* level, Sprite* sprite, Tile* startTile, Vector2 facing) {
	Entity* newEntity = NULL;

	switch (gid) {
		case GID_ENTITY_BOX:
			newEntity = DBG_NEW BoxEntity(level, sprite, startTile);
			break;
		case GID_ENTITY_BAT:
			newEntity = DBG_NEW BatEntity(level, sprite, startTile);
			break;
		case GID_ENTITY_PLAYER:
			newEntity = DBG_NEW PlayerEntity(ENTITY_PLAYER, level, sprite, startTile, facing);
			break;
	}
	if (newEntity) { 
		_allEntities.push_back(newEntity);
	}
}


void EntityManager::draw() {
	for (int i = 0; i < _allEntities.size(); i++)
	{
		_allEntities[i]->draw();
	}
}

void EntityManager::update(int deltaTime) {
	for (int i = 0; i < _allEntities.size(); i++)
	{
		_allEntities[i]->update(deltaTime);
	}
}

void EntityManager::undoAll(int turn) {
	for (int i = 0; i < _allEntities.size(); i++)
	{
		_allEntities[i]->undo(turn);
	}
	sortEntities();
}

void EntityManager::resetAll() {
	for (int i = 0; i < _allEntities.size(); i++)
	{
		_allEntities[i]->reset();
	}
	sortEntities();
}

void EntityManager::clearEntities() {
	for (int i = 0; i < _allEntities.size(); i++)
	{
		delete _allEntities[i];
	}
	_allEntities.clear();
}

void EntityManager::sortEntities()
{
	int numEntities = _allEntities.size();
	for (int i = 0; i < numEntities - 1; i++)
	{
		for (int j = 0; j < numEntities - i - 1; j++)
		{
			int a = _allEntities[j]->getCoordinate().y;
			int b = _allEntities[j + 1]->getCoordinate().y;
			if (a > b) {
				Entity* temp = _allEntities[j];
				_allEntities[j] = _allEntities[j + 1];
				_allEntities[j + 1] = temp;
			}
		}
	}
}
