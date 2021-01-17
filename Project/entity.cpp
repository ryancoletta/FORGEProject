#include "globals.h"
#include "entity.h"
#include "level.h"
#include "spriteinstance.h"
#include "tile.h"

Entity::Entity(EntityType entityID, Level* level, Sprite* sprite, Tile* startTile) :
	_entityType(entityID),
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

EntityType Entity::getEntityType() const { return _entityType; }

Tile* Entity::getTile() const { return _tileHistory.top(); }

Vector2 Entity::getCoordinate() const { return getTile()->getCoordinate(); }

bool Entity::canMove(Vector2 direction) const {
	Vector2 newCoordinate = _tileHistory.top()->getCoordinate() + direction;
	if (_level->isCoordinateInRange(newCoordinate)) {
		Tile* newTile = _level->getTile(newCoordinate);
		if (newTile->isBlocked()) {
			return false;
		}
		else if (newTile->isOccupied()) {
			Entity* toPush = newTile->getOccupant();
			if (!toPush->canMove(direction)) {
				return false;
			}
		}
		return true;
	}
	return false;
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
	while (_tileHistory.size() > 1 && _lastTurnMoved.top() >= turn) {
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
	// if someone is in this spot, make sure they perform their reset first
	if (_tileHistory.top()->isOccupied()) {
		_tileHistory.top()->getOccupant()->reset();
	}

	_tileHistory.top()->occupy(this);
}

void Entity::update(int deltaTime) {
	_sprite->update(deltaTime);
}

void Entity::draw() {
	_sprite->draw(_tileHistory.top()->getPosition());
}

void Entity::getAllConnected(std::vector<Entity*> &entities, EntityType flags) {
	entities.push_back(this);
	for (int r = 0; r < 4; r++) {
		int x = sin(r * M_PI / 2.0);
		int y = cos(r * M_PI / 2.0);
		Vector2 adjacentCoordinate = _tileHistory.top()->getCoordinate() + Vector2(x,y);
		if (_level->isCoordinateInRange(adjacentCoordinate)) {
			Tile* adjacentTile = _level->getTile(adjacentCoordinate);
			if (adjacentTile->isOccupied()) {
				Entity* neighbor = adjacentTile->getOccupant();
				if ((std::count(entities.begin(), entities.end(), neighbor) == 0) &&
					(((1 << neighbor->getEntityType()) & flags) > 0))
				{
					neighbor->getAllConnected(entities, flags);
				}
			}
		}
	}
}