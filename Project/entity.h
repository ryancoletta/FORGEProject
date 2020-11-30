#pragma once
#include <stack>
#include <vector>
#include "globals.h"
class Level;
class Tile;
class Sprite;

enum EntityType {
	ENTITY_PLAYER	= 19,
	ENTITY_BOX		= 21,
	ENTITY_CHICKEN	= 22,
};
inline EntityType operator|(EntityType a, EntityType b)
{
	return static_cast<EntityType>((1 << static_cast<int>(a)) | (1 << static_cast<int>(b)));
}

class Entity
{
public:
	Entity();
	Entity(EntityType entityID, Level* level, Sprite* sprite, Tile* startTile);
	int getEntityID();
	Tile* getTile();
	Vector2 getCoordinate();
	void draw();
	void update(int deltaTime);
	bool canMove(Vector2 direction);
	virtual bool move(int turn, Vector2 direction);
	void undo(int turn);
	void reset();
	void getAllConnected(std::vector<Entity*> &entities, EntityType flags);
private:
	EntityType _entityID;
	Level* _level;
	Sprite* _sprite;
	std::stack<Tile*> _tileHistory;
	std::stack<int> _lastTurnMoved;
};
