#pragma once
#include "tile.h"

class LevelManager;

class ExitTile : public Tile
{
public:
	ExitTile(LevelManager* levelManager, Sprite* sprite, Vector2 coordinate, Vector2 position);

protected:
	void onOccupy(int turn, EntityType outgoing = ENTITY_NONE) override;

	LevelManager* _levelManager;
};

