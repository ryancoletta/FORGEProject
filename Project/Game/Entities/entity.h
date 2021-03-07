#pragma once
#include <stack>
#include <vector>
#include "globals.h"

class Level;
class Tile;
class Sprite;

class Entity
{
public:
	Entity(EntityType entityID, Level* level, Sprite* sprite, Tile* startTile);
	virtual ~Entity() {}

	EntityType getEntityType() const;
	Tile* getTile() const;
	Sprite* getSprite() const;
	glm::vec2 getCoordinate() const;
	bool isAlive() const;

	virtual bool canMove(glm::vec2 direction) const;
	virtual bool move(int turn, glm::vec2 direction, EntityType pushingEntityType = ENTITY_NONE);
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
