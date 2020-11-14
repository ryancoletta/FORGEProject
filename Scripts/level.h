#pragma once
#include "tile.h"
#include <vector>
#include "sprite.h"
class Level
{
public:
	Level();
	Level(int rows, int cols, Sprite* sprite);

	bool isCoordinateInRange(int x, int y);
	bool isCoordinateInRange(Vector2 coordinate);
	Tile* getTile(int x, int y);
	Tile* getTile(Vector2 coordinate);
	void draw();
private:
	Sprite* _sprite;
	int _rows;
	int _cols;
	std::vector<std::vector<Tile>> _tiles;
};

