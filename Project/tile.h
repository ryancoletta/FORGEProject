#pragma once
#include "globals.h"

class Entity;
class Sprite;

enum TileType {
	TILE_WALL = 8,
	TILE_OPEN = 15,
	TILE_EXIT = 16,
};

class Tile
{
public:
	Tile();
	Tile(Sprite* sprite, Vector2 coordinate, Vector2 position);
	~Tile();
	Vector2 getCoordinate();
	Vector2 getPosition();
	Sprite* getSprite();
	Entity* getOccupant();
	bool isOccupied();
	void vacate();
	void occupy(Entity* entityToOccupy);
	void draw();
protected:
	virtual void onVacate();
	virtual void onOccupy();
private:
	Entity* _occupant;
	Sprite* _sprite;
	Vector2 _coordinate;
	Vector2 _position;
};

