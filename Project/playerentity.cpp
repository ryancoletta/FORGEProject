#include "globals.h"
#include "level.h"
#include "tile.h"
#include "playerentity.h"

PlayerEntity::PlayerEntity(EntityType entityID, Level* level, Sprite* sprite, Tile* startTile) :
	Entity(entityID, level, sprite, startTile)
{
	_facingHistory.push(Vector2::down());
}

bool PlayerEntity::move(int turn, Vector2 direction) {
	int dot = Vector2::dot(direction, _facingHistory.top());
	switch (dot) {
		case 0:
			return turnTowards(turn, direction);
		case 1:
			if (!Entity::canMove(direction * 2)) { return false; } // TODO many things wrong with this
		default:
			return Entity::move(turn, direction);
	}
}

void PlayerEntity::undo(int turn) {
	if (_facingHistory.size() > 1 && _lastTurnTurned.top() == turn) {
		_facingHistory.pop();
		_lastTurnTurned.pop();
	}
	Entity::undo(turn);
}
bool PlayerEntity::turnTowards(int turn, Vector2 direction) {
	
	Vector2 currentCoordinate = _tileHistory.top()->getCoordinate();
	Vector2 diagonalCoordinate = currentCoordinate + _facingHistory.top() + direction;
	if (_level->isCoordinateInRange(diagonalCoordinate)) {
		Tile* diagonalTile = _level->getTile(diagonalCoordinate);
		if (diagonalTile->isBlocked()) {
			return false;
		}
		else if (diagonalTile->isOccupied()) {
			Entity* toPush = diagonalTile->getOccupant();
			if (!toPush->move(turn, direction)) {
				return false;
			}
		}
	}

	Vector2 adjacentCoordinate = currentCoordinate + direction;
	if (_level->isCoordinateInRange(adjacentCoordinate)) {
		Tile* adjacentTile = _level->getTile(adjacentCoordinate);
		if (adjacentTile->isBlocked()) {
			return false;
		}
		else if (adjacentTile->isOccupied()) {
			Entity* toPush = adjacentTile->getOccupant();
			if (!toPush->move(turn, -_facingHistory.top())) {
				return false;
			}
		}
	}

	_facingHistory.push(direction);
	_lastTurnTurned.push(turn);
	return true;
}

void PlayerEntity::reset() {
	while (_lastTurnTurned.size() > 0) {
		_facingHistory.pop();
		_lastTurnTurned.pop();
	}
	Entity::reset();
}