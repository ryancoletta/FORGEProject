#include "entity.h"
#include "level.h"

Entity::Entity() :
	_level(NULL),
	_sprite(NULL),
	_currentTile(NULL)
{}
Entity::Entity(Level* grid, Sprite* sprite, Tile* startTile) : 
	_level(grid), 
	_sprite(sprite), 
	_currentTile(startTile) 
{}

void Entity::draw() {
	_sprite->draw(_currentTile->getPosition());
}

void Entity::move(Vector2 direction) {
	
	Vector2 newCoordinate = _currentTile->getCoordinate() + direction;
	if (_level->isCoordinateInRange(newCoordinate)) {
		_currentTile = _level->getTile(newCoordinate);
	}
}

void Entity::update(int deltaTime) {
	_sprite->update(deltaTime);
}