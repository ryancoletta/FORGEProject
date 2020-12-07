#include "globals.h"
#include "entitymanager.h"
#include "entity.h"
#include "level.h"
#include "sprite.h"
#include "tile.h"
#include "playerentity.h"

void EntityManager::addEntity(EntityType entityType, Level* level, Sprite* sprite, Tile* startTile) {
	Entity* newEntity;
	switch (entityType) {
		case ENTITY_PLAYER:
			newEntity = DBG_NEW PlayerEntity(entityType, level, sprite, startTile);
			break;
		default:
			newEntity = DBG_NEW Entity(entityType, level, sprite, startTile);
			break;
	}

	_allEntities.insert(std::pair<EntityType, Entity*>(entityType, newEntity));
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
	Entity* player = GetPlayerEntity();
	static_cast<PlayerEntity*>(player)->updateFlock();
}
void EntityManager::resetAll() {
	std::multimap<EntityType, Entity*>::iterator it;
	for (it = _allEntities.begin(); it != _allEntities.end(); it++)
	{
		it->second->reset();
	}
	Entity* player = GetPlayerEntity();
	static_cast<PlayerEntity*>(player)->updateFlock();
}
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
void EntityManager::clearEntities() {
	std::multimap<EntityType, Entity*>::iterator it;
	for (it = _allEntities.begin(); it != _allEntities.end(); it++)
	{
		delete it->second;
	}
	_allEntities.clear();
}
EntityManager::~EntityManager() {
	clearEntities();
}