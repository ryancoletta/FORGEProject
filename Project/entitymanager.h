#pragma once
#include <vector>
#include <memory>

class Entity;

class EntityManager 
{
public:
	void addEntity(Entity* entity);
	void draw();
	void update(int deltaTime);
private:
	// TODO store as pointers and get polymorphism OR store as copies and have a place for the memory to live w/o fear of destruction
	// are dynamic mem / smart pointers the solution??
	std::vector<Entity*> _allEntities;
};

