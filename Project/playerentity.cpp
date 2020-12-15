#include "globals.h"
#include "level.h"
#include "tile.h"
#include "playerentity.h"
#include "animatedsprite.h"

PlayerEntity::PlayerEntity(EntityType entityID, Level* level, Sprite* sprite, Tile* startTile, Vector2 facing) :
	Entity(entityID, level, sprite, startTile)
{
	_facingHistory.push(facing);
}

bool PlayerEntity::move(int turn, Vector2 direction) {
	int dot = Vector2::dot(direction, _facingHistory.top());
	switch (dot) {
		case 0:
			return turnTowards(turn, direction);
		case 1: {
			Vector2 aheadCoordinate = _tileHistory.top()->getCoordinate() + direction * 2;
			Tile* aheadTile = _level->getTile(aheadCoordinate);
			if (aheadTile->isBlocked()) {
				return false;
			}
			else if (aheadTile->isOccupied()) {
				Entity* toPush = aheadTile->getOccupant();
				if (!toPush->move(turn, direction)) {
					return false;
				}
			}
		}
		default:
			return Entity::move(turn, direction);
	}
}

bool PlayerEntity::turnTowards(int turn, Vector2 direction) {
	
	// store top up here so we can use throughout without fear of modifying the stack and for speed, also for readability
	Vector2 playerFacingDirection = _facingHistory.top();
	Vector2 currentCoordinate = _tileHistory.top()->getCoordinate();

	Vector2 diagonalCoordinate = currentCoordinate + playerFacingDirection + direction;
	Entity* diagonalEntity = NULL;
	if (_level->isCoordinateInRange(diagonalCoordinate)) {
		Tile* diagonalTile = _level->getTile(diagonalCoordinate);
		if (diagonalTile->isBlocked()) {
			return false;
		}
		else if (diagonalTile->isOccupied()) {
			diagonalEntity = diagonalTile->getOccupant();
			if (!diagonalEntity->canMove(direction)) {
				return false;
			}
		}
	}

	Vector2 adjacentCoordinate = currentCoordinate + direction;
	Entity* adjacentEntity = NULL;
	if (_level->isCoordinateInRange(adjacentCoordinate)) {
		Tile* adjacentTile = _level->getTile(adjacentCoordinate);
		if (adjacentTile->isBlocked()) {
			return false;
		}
		else if (adjacentTile->isOccupied()) {
			adjacentEntity = adjacentTile->getOccupant();

			if (!adjacentEntity->canMove(-playerFacingDirection)) {
				return false;
			}
		}
	}

	if (diagonalEntity) { diagonalEntity->move(turn, direction); }
	if (adjacentEntity) { adjacentEntity->move(turn, -playerFacingDirection); }

	playTurnAnimation(direction);

	_facingHistory.push(direction);
	_lastTurnTurned.push(turn);
	return true;
}

void PlayerEntity::playTurnAnimation(Vector2 direction) {
	if (direction == Vector2::up()) {
		static_cast<AnimatedSprite*>(_sprite)->playAnimation("down");
	}
	else if (direction == Vector2::right()) {
		static_cast<AnimatedSprite*>(_sprite)->playAnimation("right");
	}
	else if (direction == Vector2::down()) {
		static_cast<AnimatedSprite*>(_sprite)->playAnimation("up");
	}
	else if (direction == Vector2::left()) {
		static_cast<AnimatedSprite*>(_sprite)->playAnimation("left");
	}
}

// TODO bug when hitting undo after having pushed and adjacent object; the stack appears to change values!!!
void PlayerEntity::undo(int turn) {
	if (_facingHistory.size() > 1 && _lastTurnTurned.top() == turn) {
		_facingHistory.pop();
		_lastTurnTurned.pop();
		playTurnAnimation(_facingHistory.top());
	}

	Entity::undo(turn);
}

void PlayerEntity::reset() {
	while (_lastTurnTurned.size() > 0) {
		_facingHistory.pop();
		_lastTurnTurned.pop();
	}
	playTurnAnimation(_facingHistory.top());
	Entity::reset();
}