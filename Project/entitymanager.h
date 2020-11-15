#pragma once
#include <vector>
#include "entity.h"

class EntityManager 
{
public:
	void addEntity(Entity* entity);
	void draw();
	void update(int deltaTime);
private:
	std::vector<Entity*> _allEntities;
};

