#pragma once
#include <stack>
#include "globals.h"

class Entity;
class Sprite;
enum EntityType;

class Tile
{
public:
	Tile(TileType tileType, Sprite* sprite, glm::vec2 coordinate, glm::vec2 position, bool blocked = false);
	virtual ~Tile() {}

	TileType getTileType() const;
	glm::vec2 getCoordinate() const;
	glm::vec2 getPosition() const;
	Sprite* getSprite() const;
	Entity* getOccupant() const;
	virtual bool isBlocked(EntityType entrant) const;
	bool isOccupied() const;

	void setBlocked(bool blocked);

	void vacate(int turn, EntityType incoming = ENTITY_NONE);
	void occupy(Entity* entityToOccupy, int turn, EntityType outgoing = ENTITY_NONE);
	void draw();
	void update(int deltaTimeMs);

	virtual void undo(int turn) {}
	virtual void reset() {}

protected:
	virtual void onVacate(int turn, EntityType incoming = ENTITY_NONE);
	virtual void onOccupy(int turn, EntityType outgoing = ENTITY_NONE);

	bool _blocked;
	TileType _tileType;
	std::stack<Entity*> _occupant;
	Sprite* _sprite;
	glm::vec2 _coordinate;
	glm::vec2 _position;
};

