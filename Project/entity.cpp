#include "globals.h"
#include "entity.h"
#include "level.h"
#include "sprite.h"
#include "tile.h"

Entity::Entity(EntityType entityID, Level* level, Sprite* sprite, Tile* startTile) :
	_entityType(entityID),
	_level(level),
	_sprite(sprite),
	_isAlive(true)
{
	if (startTile->isOccupied()) {
		printf("ERROR: attempting to place entity on an occupied tile");
	}
	else {
		_tileHistory.push(startTile);
		startTile->occupy(this, 0);
	}
}

EntityType Entity::getEntityType() const { return _entityType; }

Tile* Entity::getTile() const { return _tileHistory.top(); }

Sprite* Entity::getSprite() const { return _sprite; }

Vector2 Entity::getCoordinate() const { return getTile()->getCoordinate(); }

bool Entity::isAlive() const { return _isAlive; }

bool Entity::canMove(Vector2 direction) const {
	Vector2 newCoordinate = _tileHistory.top()->getCoordinate() + direction;
	if (_level->isCoordinateInRange(newCoordinate)) {
		Tile* newTile = _level->getTile(newCoordinate);
		if (newTile->isBlocked(_entityType)) {
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

bool Entity::move(int turn, Vector2 direction, EntityType pushingEntityType) {
	Vector2 newCoordinate = _tileHistory.top()->getCoordinate() + direction;
	if (_level->isCoordinateInRange(newCoordinate)) {
		Tile* newTile = _level->getTile(newCoordinate);
		Entity* toPush = nullptr;
		if (newTile->isBlocked(_entityType)) {
			return false;
		}
		else if (newTile->isOccupied()) {
			toPush = newTile->getOccupant();

			assert(toPush != this); // stop pushing yourself!

			if (!toPush->move(turn, direction, _entityType)) {
				return false;
			}
		}

		bool pushingEntityIsGrounded = (pushingEntityType & ENTITY_GROUNDED) > 0;
		bool thisEntityIsGrounded = (_entityType & ENTITY_GROUNDED) > 0;
		bool pushedEntityIsGrounded = toPush ? (toPush->getEntityType() & ENTITY_GROUNDED) > 0 : false;
		_tileHistory.top()->vacate(turn, !pushingEntityIsGrounded && thisEntityIsGrounded);
		_tileHistory.push(newTile);
		_tileHistory.top()->occupy(this, turn, !pushedEntityIsGrounded && thisEntityIsGrounded);
		_lastTurnMoved.push(turn);

		return true;
	}
	return false;
}

void Entity::undo(int turn) {
	while (_lastTurnMoved.size() > 0 && _lastTurnMoved.top() >= turn) {
		// revive
		if (!_isAlive) {
			revive();
			if (_tileHistory.top()->isOccupied()) {
				_tileHistory.top()->getOccupant()->undo(turn); // if this tile is already occupied, let them go first
			}
			_tileHistory.top()->occupy(this, turn, false); 
			continue;
		}

		// undo move
		_tileHistory.top()->vacate(turn, false);
		_tileHistory.pop();

		// if someone is in this spot, make sure they perform their undo first
		if (_tileHistory.top()->isOccupied()) { // DEAD OBJECTS REGISTER AS NON OCCUPIED
			_tileHistory.top()->getOccupant()->undo(turn);
		}

		_tileHistory.top()->occupy(this, turn, false);
		_lastTurnMoved.pop();
	}
}

void Entity::reset() {
	// revive if dead
	if (!_isAlive) {
		revive();
	}
	else {
		_tileHistory.top()->vacate(0, false);
	}

	// find the first tile in your history
	while (_lastTurnMoved.size() > 0) {
		_tileHistory.pop();
		_lastTurnMoved.pop();
	}

	// if someone is in said tile, make sure they perform their reset first
	if (_tileHistory.top()->isOccupied()) {
		_tileHistory.top()->getOccupant()->reset();
	}

	// occupy your original tile
	_tileHistory.top()->occupy(this, 0, false);
}

void Entity::update(int deltaTime) {
	_sprite->update(deltaTime);
}

void Entity::draw() {
	assert(_sprite != nullptr);

	_sprite->draw(_tileHistory.top()->getPosition());
}

void Entity::kill(int turn)
{
	assert(_isAlive); // should not kill after already killed

	_isAlive = false;
	_lastTurnMoved.push(turn);
	_tileHistory.top()->vacate(turn);
	_sprite->setSortingOrder(-1);
}

void Entity::revive()
{
	_isAlive = true;
	_lastTurnMoved.pop();
	_sprite->setSortingOrder(0);
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