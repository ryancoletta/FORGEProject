#pragma once
#include "globals.h"
#include "entity.h"
#include <stack>

class DirectionalEntity : public Entity
{
public:
	DirectionalEntity(EntityType entityID, Level* level, Sprite* sprite, Tile* startTile, glm::vec2 facing);
	virtual ~DirectionalEntity() {}

	glm::vec2 getDirectionFacing();
	void undo(int turn) override;
	void reset() override;
	//void draw() override;
protected:
	std::stack<glm::vec2> _facingHistory;
	std::stack<int> _lastTurnTurned;
};

