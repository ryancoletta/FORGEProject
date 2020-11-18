#pragma once
#include "globals.h"

class Sprite;

class Tile
{
public:
	Tile();
	Tile(Sprite* sprite, Vector2 coordinate, Vector2 position);
	Vector2 getCoordinate();
	Vector2 getPosition();
	Sprite* getSprite();
	void draw();
private:
	Sprite* _sprite;
	Vector2 _coordinate;
	Vector2 _position;
};

