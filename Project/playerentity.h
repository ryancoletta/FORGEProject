#pragma once
#include "globals.h"
#include "directionalentity.h"
#include <stack>

class PlayerEntity : public DirectionalEntity
{
public:
	PlayerEntity(EntityType entityID, Level* level, Sprite* sprite, Tile* startTile, Vector2 facing);

	bool move(int turn, Vector2 direction) override;
	void draw();

private:
	bool turnTowards(int turn, Vector2 direction);

	Sprite* _sword;
};

