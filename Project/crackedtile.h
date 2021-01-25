#pragma once
#include "globals.h"
#include "tile.h"
#include <stack>

class Sprite;
enum EntityType;

class CrackedTile : public Tile
{
public:
	CrackedTile(int progress, Sprite* sprite, Vector2 coordinate, Vector2 position);
	void onOccupy(int turn) override;
	void onVacate(int turn) override;
	bool isBlocked(EntityType entrant) const override;
	void undo(int turn) override;
	void reset() override;
private:
	int _crackProgress;
	std::stack<int> _lastTurnCracked;
};

