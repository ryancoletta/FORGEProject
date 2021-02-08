#pragma once
#include "tile.h"
#include <stack>

class DynamicTile : public Tile
{
public:
	DynamicTile(TileType tileType, Sprite* sprite, Vector2 coordinate, Vector2 position, int startingStage);
	void undo(int turn) override;
	void reset() override;
protected:
	std::stack<int> _stageHistory;
	std::stack<int> _lastTurnModified;
};

