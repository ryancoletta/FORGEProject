#include "entity.h"
#include "grid.h"

Entity::Entity() {}
Entity::Entity(Grid* grid, Sprite* sprite, Tile startTile) : _grid(grid), _sprite(sprite), _currentTile(startTile) {
	_sprite->setPosition(_currentTile.getPosition());
}

void Entity::draw() {
	_sprite->draw();
}

void Entity::move(Vector2 direction) {
	
	Vector2 newCoordinate = _currentTile.getCoordinate() + direction;
	if (_grid->isCoordinateInRange(newCoordinate)) {
		_currentTile = _grid->getTile(newCoordinate);
		_sprite->setPosition(_currentTile.getPosition());
	}
}

void Entity::update(int deltaTime) {
	_sprite->update(deltaTime);
}