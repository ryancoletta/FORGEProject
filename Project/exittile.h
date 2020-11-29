#pragma once
#include "tile.h"

class Game;

class ExitTile : public Tile
{
public:
	ExitTile();
	ExitTile(Game* game, Sprite* sprite, Vector2 coordinate, Vector2 position);
protected:
	void onOccupy() override;
	Game* _game;
};

