#pragma once
#include "tile.h"
#include <stack>

class SpikeTile : public Tile
{
public:
	SpikeTile(Sprite* sprite, Vector2 coordinate, Vector2 position, bool isOn);
	void toggleSpikes(int turn);
	void undo(int turn) override;
	void reset() override;
	bool isBlocked(EntityType entrant) const override;
protected:
	void onOccupy(int turn) override;
private:
	void tryHurtOccupant(int turn);
	bool _isOn;
	std::stack<int> _lastTurnToggled;
};

