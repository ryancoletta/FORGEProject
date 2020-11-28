#pragma once
#include <stack>
#include "globals.h"
class Level;
class Tile;
class Sprite;

enum EntityType {
	ENTITY_PLAYER	= 28,
	ENTITY_BOX		= 30,
	ENTITY_CHICKEN	= 31,
};

class Entity
{
public:
	Entity();
	Entity(EntityType entityID, Level* level, Sprite* sprite, Tile* startTile);
	int getEntityID();
	void draw();
	void update(int deltaTime);
	bool move(int turn, Vector2 direction);
	void undo(int turn);
	void reset();
private:
	EntityType _entityID;
	Level* _level;
	Sprite* _sprite;
	std::stack<Tile*> _tileHistory;
	std::stack<int> _lastTurnMoved;
};
