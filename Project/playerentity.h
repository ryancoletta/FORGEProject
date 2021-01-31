#pragma once
#include "globals.h"
#include "directionalentity.h"
#include <stack>

class PlayerEntity : public DirectionalEntity
{
public:
	PlayerEntity(EntityType entityID, Level* level, Sprite* sprite, Tile* startTile, Vector2 facing);

	bool move(int turn, Vector2 direction) override;

	void kill(int turn) override; // TODO replace with virtual

	void updateAnimation();
	void undo(int turn) override;
	void reset() override;

private:
	bool turnTowards(int turn, Vector2 direction);
};

