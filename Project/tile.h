#pragma once
#include "globals.h"

class Entity;
class Sprite;

enum TileType {
	TILE_WALL = 1 << 0,
	TILE_OPEN = 1 << 1,
	TILE_GOAL = 1 << 2,
	TILE_SWITCH = 1 << 3,
	TILE_SPIKE = 1 << 4,
};

class Tile
{
public:
	Tile(TileType tileType, Sprite* sprite, Vector2 coordinate, Vector2 position, bool blocked = false);
	virtual ~Tile() {}

	TileType getTileType() const;
	Vector2 getCoordinate() const;
	Vector2 getPosition() const;
	Sprite* getSprite() const;
	Entity* getOccupant() const;
	bool isBlocked() const;
	bool isOccupied() const;

	void setBlocked(bool blocked);

	void vacate();
	void occupy(Entity* entityToOccupy);
	void draw();

protected:
	virtual void onVacate();
	virtual void onOccupy();

	bool _blocked;
	TileType _tileType;
	Entity* _occupant;
	Sprite* _sprite;
	Vector2 _coordinate;
	Vector2 _position;
};

