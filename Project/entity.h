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
	Sprite* _sprite; // TODO store as pointer and get polymorphism OR store as a copy and have a place for the memory to live w/o fear of destruction
	Tile* _currentTile;
};
