#include "entity.h"
#include "level.h"
#include "sprite.h"
#include "tile.h"

Entity::Entity() :
	_entityID(0),
	_level(NULL),
	_sprite(NULL),
	_currentTile(NULL)
{}
Entity::Entity(int entityID, Level* level, Sprite* sprite, Tile* startTile) :
	_entityID(entityID),
	_level(level),
	_sprite(sprite), 
	_currentTile(startTile) 
{}
int Entity::getEntityID() { return _entityID; }
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