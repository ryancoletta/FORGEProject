#pragma once
#include "sprite.h"
#include "tile.h"
#include "grid.h"

class Entity
{
public:
	Entity();
	Entity(Grid* grid, Sprite* sprite, Tile startTile);
	void draw();
	void update(int deltaTime);
	void move(Vector2 direction);
private:
	Grid* _grid;
	Sprite* _sprite;
	Tile _currentTile;
};

