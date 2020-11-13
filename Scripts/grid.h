#pragma once
#include "tile.h"
#include <vector>
class Grid
{
public:
	Grid();
	Grid(int rows, int cols);

	bool isCoordinateInRange(int x, int y);
	bool isCoordinateInRange(Vector2 coordinate);
	Tile getTile(int x, int y);
	Tile getTile(Vector2 coordinate);
private:
	int _rows;
	int _cols;
	std::vector<std::vector<Tile>> _tiles;
};

