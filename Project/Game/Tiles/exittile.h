#pragma once
#include "tile.h"

class LevelManager;

class ExitTile : public Tile
{
public:
	ExitTile(LevelManager* levelManager, Sprite* sprite, glm::vec2 coordinate, glm::vec2 position);

protected:
	void onOccupy(int turn, EntityType outgoing = ENTITY_NONE) override;

	LevelManager* _levelManager;
};

