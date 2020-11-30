#pragma once
#include "globals.h"

class Entity;
class Sprite;

enum TileType {
	TILE_WALL = 13,
	TILE_OPEN = 14,
	TILE_GOAL = 15,
};

class Tile
{
public:
	Tile();
	Tile(TileType tileType, Sprite* sprite, Vector2 coordinate, Vector2 position, bool blocked = false);
	~Tile();
	void setBlocked(bool blocked);
	bool isBlocked();
	TileType getTileType();
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

	TileType _tileType;
	Entity* _occupant;
	Sprite* _sprite;
	Vector2 _coordinate;
	Vector2 _position;
	bool _blocked;
};

