#pragma once
#include "globals.h"
#include "entity.h"
#include <stack>

class DirectionalEntity : public Entity
{
public:
	DirectionalEntity(EntityType entityID, Level* level, Sprite* sprite, Tile* startTile, Vector2 facing);
	virtual ~DirectionalEntity() {}

	Vector2 getDirectionFacing();
	void undo(int turn) override;
	void reset() override;
	void draw() override;
protected:
	std::stack<Vector2> _facingHistory;
	std::stack<int> _lastTurnTurned;
};

