#pragma once
#include "globals.h"
#include <map>
#include <vector>
#include <memory>

class Entity;
class Level;
class SpriteInstance;
class Tile;

enum GidElement;
enum EntityType;

class EntityManager 
{
public:
	~EntityManager();

	std::vector<Entity*> GetEntitiesByType(EntityType entityType);
	Entity* GetPlayerEntity();

	void addEntity(GidElement gid, Level* grid, SpriteInstance* sprite, Tile* startTile, Vector2 facing);
	void draw();
	void update(int deltaTime);
	void undoAll(int turn);
	void resetAll();
	void clearEntities();

private:
	std::multimap<EntityType, Entity*> _allEntities;
};



