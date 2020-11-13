#pragma once
#include "globals.h"

class Tile
{
public:
	Tile();
	Tile(Vector2 coordinate, Vector2 position);
	Vector2 getCoordinate();
	Vector2 getPosition();
private:
	Vector2 _coordinate;
	Vector2 _position;
};

