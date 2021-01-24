#pragma once
#include "globals.h"
#include "directionalentity.h"
#include <stack>

class PlayerEntity : public DirectionalEntity
{
public:
	PlayerEntity(EntityType entityID, Level* level, Sprite* sprite, Tile* startTile, Vector2 facing);

	bool isAlive();
	bool move(int turn, Vector2 direction) override;

	void kill();

	void updateAnimation();
	void undo(int turn) override;
	void reset() override;

private:
	bool turnTowards(int turn, Vector2 direction);
	bool _isAlive;
	Sprite* _sword;
};

