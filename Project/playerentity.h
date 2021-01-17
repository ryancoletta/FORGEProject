#pragma once
#include "globals.h"
#include "directionalentity.h"
#include <stack>

class PlayerEntity : public DirectionalEntity
{
public:
	PlayerEntity(EntityType entityID, Level* level, SpriteInstance* sprite, Tile* startTile, Vector2 facing);

	bool move(int turn, Vector2 direction) override;

private:
	bool turnTowards(int turn, Vector2 direction);
};

