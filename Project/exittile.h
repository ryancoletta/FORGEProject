#pragma once
#include "tile.h"

class LevelManager;

class ExitTile : public Tile
{
public:
	ExitTile(LevelManager* levelManager, Sprite* sprite, Vector2 coordinate, Vector2 position);

protected:
	void onOccupy(int turn) override;

	LevelManager* _levelManager;
};

