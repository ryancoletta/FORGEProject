#pragma once
#include "entity.h"

class BatEntity : public Entity
{
public:
	BatEntity(Level* level, Sprite* sprite, Tile* startTile);
	void kill(int turn) override;
	void undo(int turn) override;
	void reset() override;
};

