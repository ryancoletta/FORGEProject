#include "entity.h"
#include "level.h"
#include "sprite.h"
#include "tile.h"

Entity::Entity() :
	_entityID(ENTITY_PLAYER),
	_level(NULL),
	_sprite(NULL)
{}
Entity::Entity(EntityType entityID, Level* level, Sprite* sprite, Tile* startTile) :
	_entityID(entityID),
	_level(level),
	_sprite(sprite)
{
	if (startTile->isOccupied()) {
		printf("ERROR: attempting to place entity on an occupied tile");
	}
	else {
		_tileHistory.push(startTile);
		startTile->occupy(this);
	}
}
int Entity::getEntityID() { return _entityID; }
void Entity::draw() {
	_sprite->draw(_tileHistory.top()->getPosition());
}

bool Entity::move(int turn, Vector2 direction) {
	Vector2 newCoordinate = _tileHistory.top()->getCoordinate() + direction;
	if (_level->isCoordinateInRange(newCoordinate)) {
		Tile* newTile = _level->getTile(newCoordinate);
		if (newTile->isBlocked()) {
			return false;
		}
		else if (newTile->isOccupied()) {
			Entity* toPush = newTile->getOccupant();
			if (!toPush->move(turn, direction)) {
				return false;
			}
		}
		_tileHistory.top()->vacate();
		_tileHistory.push(newTile);
		_tileHistory.top()->occupy(this);
		_lastTurnMoved.push(turn);

		return true;
	}
	return false;
}

void Entity::undo(int turn) {
	if (_tileHistory.size() > 1 && _lastTurnMoved.top() == turn) {
		_tileHistory.top()->vacate();
		_tileHistory.pop();

		// if someone is in this spot, make sure they perform their undo first
		if (_tileHistory.top()->isOccupied()) {
			_tileHistory.top()->getOccupant()->undo(turn);
		}

		_tileHistory.top()->occupy(this);
		_lastTurnMoved.pop();
	}
}

void Entity::reset() {
	_tileHistory.top()->vacate();
	while (_lastTurnMoved.size() > 0) {
		_tileHistory.pop();
		_lastTurnMoved.pop();
	}
	_tileHistory.top()->occupy(this);
}

void Entity::update(int deltaTime) {
	_sprite->update(deltaTime);
}