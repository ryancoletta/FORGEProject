#pragma once
#include "dynamictile.h"
#include <stack>

class SpikeTile : public DynamicTile
{
public:
	SpikeTile(Sprite* sprite, Vector2 coordinate, Vector2 position, int startingStage);
	void toggleSpikes(int turn);
	void undo(int turn) override;
	void reset() override;
	bool isBlocked(EntityType entrant) const override;
protected:
	void onOccupy(int turn) override;
private:
	void tryHurtOccupant(int turn);
};

