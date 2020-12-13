#pragma once
#include "globals.h"
#include "entity.h"
#include <stack>

class PlayerEntity : public Entity
{
public:
	PlayerEntity(EntityType entityID, Level* level, Sprite* sprite, Tile* startTile, Vector2 startFacing);

	bool move(int turn, Vector2 direction) override;
	void undo(int turn) override;
	void reset() override;


private:
	bool turnTowards(int turn, Vector2 direction);
	void playTurnAnimation(Vector2 direction);

	std::stack<Vector2> _facingHistory;
	std::stack<int> _lastTurnTurned;
};

