#pragma once
#include <vector>
#include <memory>

class Entity;
class Level;
class Sprite;
class Tile;

class EntityManager 
{
public:
	~EntityManager();
	void addEntity(int entityID, Level* grid, Sprite* sprite, Tile* startTile);
	void draw();
	void update(int deltaTime);
	Entity* GetEntitiesByType(int entityID);
private:
	// TODO store as pointers and get polymorphism OR store as copies and have a place for the memory to live w/o fear of destruction
	// are dynamic mem / smart pointers the solution??
	std::vector<Entity*> _allEntities;
};

