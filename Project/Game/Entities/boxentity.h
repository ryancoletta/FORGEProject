#pragma once
#include "entity.h"
class BoxEntity : public Entity
{
public:
	BoxEntity(Level* level, Sprite* sprite, Tile* startTile);

	void kill(int turn) override;

	bool canMove(glm::vec2 direction) const override;
	void undo(int turn) override;
	void reset() override;
};

