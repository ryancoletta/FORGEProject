#include "globals.h"
#include "entitymanager.h"
#include "entity.h"
#include "level.h"
#include "sprite.h"
#include "tile.h"
#include "playerentity.h"

EntityManager::~EntityManager() { clearEntities(); }

std::vector<Entity*> EntityManager::GetEntitiesByType(EntityType entityID) {

	std::vector<Entity*> allEntitiesOfType;
	std::multimap<EntityType, Entity*>::iterator it;
	for (it = _allEntities.begin(); it != _allEntities.end(); it++)
	{
		if (it->first == entityID) {
			allEntitiesOfType.push_back(it->second);
		}
	}
	return allEntitiesOfType;
}

Entity* EntityManager::GetPlayerEntity() {
	std::vector<Entity*> playerEntities = GetEntitiesByType(ENTITY_PLAYER);
	if (playerEntities.empty()) {
		printf("ERROR: no player found in level\n");
		return NULL;
	}
	return playerEntities[0];
}

void EntityManager::addEntity(GidElement gid, Level* level, Sprite* sprite, Tile* startTile) {
	Entity* newEntity = NULL;
	switch (gid) {
		case GID_ENTITY_BOX:
			newEntity = DBG_NEW Entity(ENTITY_BOX, level, sprite, startTile);
			break;
		case GID_ENTITY_CHICKEN:
			newEntity = DBG_NEW Entity(ENTITY_CHICKEN, level, sprite, startTile);
			break;
		case GID_ENTITY_PLAYER_UP:
			newEntity = DBG_NEW PlayerEntity(ENTITY_PLAYER, level, sprite, startTile, Vector2::down());
			break;
		case GID_ENTITY_PLAYER_RIGHT:
			newEntity = DBG_NEW PlayerEntity(ENTITY_PLAYER, level, sprite, startTile, Vector2::right());
			break;
		case GID_ENTITY_PLAYER_DOWN:
			newEntity = DBG_NEW PlayerEntity(ENTITY_PLAYER, level, sprite, startTile, Vector2::up());
			break;
		case GID_ENTITY_PLAYER_LEFT:
			newEntity = DBG_NEW PlayerEntity(ENTITY_PLAYER, level, sprite, startTile, Vector2::left());
			break;
	}
	if (newEntity) { 
		_allEntities.insert(std::pair<EntityType, Entity*>(newEntity->getEntityType(), newEntity)); 
	}
}

void EntityManager::draw() {
	std::multimap<EntityType, Entity*>::iterator it;
	for (it = _allEntities.begin(); it != _allEntities.end(); it++)
	{
		it->second->draw();
	}
}

void EntityManager::update(int deltaTime) {
	std::multimap<EntityType, Entity*>::iterator it;
	for (it = _allEntities.begin(); it != _allEntities.end(); it++)
	{
		it->second->update(deltaTime);
	}
}

void EntityManager::undoAll(int turn) {
	std::multimap<EntityType, Entity*>::iterator it;
	for (it = _allEntities.begin(); it != _allEntities.end(); it++)
	{
		it->second->undo(turn);
	}
}

void EntityManager::resetAll() {
	std::multimap<EntityType, Entity*>::iterator it;
	for (it = _allEntities.begin(); it != _allEntities.end(); it++)
	{
		it->second->reset();
	}
}

void EntityManager::clearEntities() {
	std::multimap<EntityType, Entity*>::iterator it;
	for (it = _allEntities.begin(); it != _allEntities.end(); it++)
	{
		delete it->second;
		it->second = NULL;
	}
	_allEntities.clear();
}