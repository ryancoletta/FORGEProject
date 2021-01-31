#pragma once
#include "entity.h"
class BoxEntity : public Entity
{
public:
	BoxEntity(Level* level, Sprite* sprite, Tile* startTile);

	void fall(int turn);

	bool canMove(Vector2 direction) const override;
	void undo(int turn) override;
	void reset() override;
private:
	int _fallenTurn;
};

