#pragma once
#include "globals.h"
#include "dynamictile.h"

class Sprite;
enum EntityType;

class HoleTile : public DynamicTile
{
public:
	HoleTile(Sprite* sprite, Vector2 coordinate, Vector2 position);
	void onOccupy(int turn, EntityType outgoing = ENTITY_NONE) override;
	bool isBlocked(EntityType entrant) const override;
};

