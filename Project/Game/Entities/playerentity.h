#pragma once
#include "globals.h"
#include "directionalentity.h"
#include <stack>

class PlayerEntity : public DirectionalEntity
{
public:
	PlayerEntity(EntityType entityID, Level* level, Sprite* sprite, Tile* startTile, glm::vec2 facing);

	bool move(int turn, glm::vec2 direction, EntityType pushingEntityType = ENTITY_NONE) override;

	void kill(int turn) override; // TODO replace with virtual

	void updateAnimation();
	void undo(int turn) override;
	void reset() override;

private:
	bool turnTowards(int turn, glm::vec2 direction);
};

