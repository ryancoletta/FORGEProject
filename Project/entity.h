#pragma once
#include "sprite.h"
#include "tile.h"
#include "level.h"

class Entity
{
public:
	Entity();
	Entity(Level* grid, Sprite* sprite, Tile* startTile);
	void draw();
	void update(int deltaTime);
	void move(Vector2 direction);
private:
	Level* _level;
	Sprite* _sprite;
	Tile* _currentTile;
};
