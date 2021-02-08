#pragma once
#include "globals.h"
#include <vector>
#include "directionalentity.h"


class LinkedEntity : public DirectionalEntity
{
public:
	LinkedEntity(EntityType entityID, Level* level, Sprite* sprite, Tile* startTile, Vector2 facing);

	bool canMove(Vector2 direction) const override;
	bool move(int turn, Vector2 direction, EntityType pushingEntityType = ENTITY_NONE) override;

	std::vector<LinkedEntity*> Link();
private:
	std::vector<LinkedEntity*> _allLinkedEntities;
};

