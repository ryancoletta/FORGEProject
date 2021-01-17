#pragma once
#include "tile.h"

class LevelManager;

class ExitTile : public Tile
{
public:
	ExitTile(LevelManager* levelManager, SpriteInstance* sprite, Vector2 coordinate, Vector2 position);

protected:
	void onOccupy() override;

	LevelManager* _levelManager;
};

