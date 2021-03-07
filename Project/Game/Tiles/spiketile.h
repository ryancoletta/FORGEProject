#pragma once
#include "dynamictile.h"
#include <stack>

class SpikeTile : public DynamicTile
{
public:
	SpikeTile(Sprite* sprite, glm::vec2 coordinate, glm::vec2 position, int startingStage);
	void toggleSpikes(int turn);
	void undo(int turn) override;
	void reset() override;
	bool isBlocked(EntityType entrant) const override;
protected:
	void onOccupy(int turn, EntityType outgoing = ENTITY_NONE) override;
private:
	void tryHurtOccupant(int turn);
};

