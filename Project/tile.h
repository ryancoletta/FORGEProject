#pragma once
#include "globals.h"

class Entity;
class Sprite;
enum EntityType;

enum TileType {
	TILE_WALL		= 1 << 0,
	TILE_OPEN		= 1 << 1,
	TILE_GOAL		= 1 << 2,
	TILE_SWITCH		= 1 << 3,
	TILE_SPIKE		= 1 << 4,
	TILE_CRACKED	= 1 << 5,
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
	virtual bool isBlocked(EntityType entrant) const;
	bool isOccupied() const;

	void setBlocked(bool blocked);

	void vacate(int turn, bool triggerOnVacate = true);
	void occupy(Entity* entityToOccupy, int turn, bool triggerOnOccupy = true);
	void draw();
	void update(int deltaTimeMs);

	virtual void undo(int turn) {}
	virtual void reset() {}

protected:
	virtual void onVacate(int turn);
	virtual void onOccupy(int turn);

	bool _blocked;
	TileType _tileType;
	Entity* _occupant;
	Sprite* _sprite;
	Vector2 _coordinate;
	Vector2 _position;
};

