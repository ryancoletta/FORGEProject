#pragma once
#include "globals.h"
#include "dynamictile.h"

class Sprite;
enum EntityType;

class HoleTile : public DynamicTile
{
public:
	HoleTile(Sprite* sprite, glm::vec2 coordinate, glm::vec2 position);
	void onOccupy(int turn, EntityType outgoing = ENTITY_NONE) override;
	bool isBlocked(EntityType entrant) const override;
};

