#pragma once
#include <map>
#include <vector>
#include <memory>

class Entity;
class Level;
class Sprite;
class Tile;

enum EntityType;

class EntityManager 
{
public:
	~EntityManager();
	void addEntity(EntityType entityType, Level* grid, Sprite* sprite, Tile* startTile);
	void draw();
	void update(int deltaTime);
	void undoAll(int turn);
	void resetAll();
	std::vector<Entity*> GetEntitiesByType(EntityType entityType);
	Entity* GetPlayerEntity();
private:
	std::multimap<EntityType, Entity*> _allEntities;
};



