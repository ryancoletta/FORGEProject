#pragma once
#include "entity.h"
#include <vector>

class PlayerEntity : public Entity
{
public:
	PlayerEntity(EntityType entityID, Level* level, Sprite* sprite, Tile* startTile);

	bool move(int turn, Vector2 direction) override;
	void updateFlock();

private:
	void sortFlock(Vector2 direction);

	std::vector<Entity*> _flock;
};

