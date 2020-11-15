#pragma once
#include "globals.h"
class Level;
class Tile;
class Sprite;

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
