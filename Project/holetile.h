#pragma once
#include "globals.h"
#include "tile.h"
#include <stack>

class Sprite;
enum EntityType;

class HoleTile : public Tile
{
public:
	HoleTile(Sprite* sprite, Vector2 coordinate, Vector2 position);
	void onOccupy(int turn) override;
	bool isBlocked(EntityType entrant) const override;
};

