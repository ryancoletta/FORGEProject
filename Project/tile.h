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

