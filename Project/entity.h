#pragma once
#include <stack>
#include <vector>
#include "globals.h"

class Level;
class Tile;
class Sprite;

enum EntityType {
	ENTITY_NONE			= 1 << 0,
	ENTITY_BOX			= 1 << 1,
	ENTITY_BAT			= 1 << 2,
	ENTITY_PLAYER		= 1 << 3,
	ENTITY_SWORD		= 1 << 4,
	ENTITY_GROUNDED		= ENTITY_BOX | ENTITY_PLAYER,
	ENTITY_VULNERABLE	= ENTITY_BOX | ENTITY_BAT,
};

inline EntityType operator|(EntityType a, EntityType b)
{
	return static_cast<EntityType>(static_cast<int>(a) |static_cast<int>(b));
}

inline EntityType operator&(EntityType a, EntityType b)
{
	return static_cast<EntityType>(static_cast<int>(a) & static_cast<int>(b));
}

class Entity
{
public:
	Entity(EntityType entityID, Level* level, Sprite* sprite, Tile* startTile);
	virtual ~Entity() {}

	EntityType getEntityType() const;
	Tile* getTile() const;
	Sprite* getSprite() const;
	Vector2 getCoordinate() const;
	bool isAlive() const;

	virtual bool canMove(Vector2 direction) const;
	virtual bool move(int turn, Vector2 direction, EntityType pushingEntityType = ENTITY_NONE);
	virtual void undo(int turn);
	virtual void reset();
	virtual void draw();
	virtual void kill(int turn);
	virtual void revive();

	void update(int deltaTime);
	void getAllConnected(std::vector<Entity*> &entities, EntityType flags);

protected:
	EntityType _entityType;
	Level* _level;
	Sprite* _sprite;
	std::stack<Tile*> _tileHistory;
	std::stack<int> _lastTurnMoved;
	bool _isAlive;
};
