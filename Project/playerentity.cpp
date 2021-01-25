#include "globals.h"
#include "level.h"
#include "tile.h"
#include "playerentity.h"
#include "animatedsprite.h"

PlayerEntity::PlayerEntity(EntityType entityID, Level* level, Sprite* sprite, Tile* startTile, Vector2 facing) :
	DirectionalEntity(entityID, level, sprite, startTile, facing)
{}

bool PlayerEntity::isAlive()
{
	return _isAlive;
}

bool PlayerEntity::move(int turn, Vector2 direction) {
	int dot = Vector2::dot(direction, _facingHistory.top());
	switch (dot) {
		case 0:
			return turnTowards(turn, direction);
		case 1: {
			Vector2 aheadCoordinate = _tileHistory.top()->getCoordinate() + direction * 2;
			Tile* aheadTile = _level->getTile(aheadCoordinate);
			if (aheadTile->isBlocked(ENTITY_SWORD)) {
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

void PlayerEntity::kill()
{
	_isAlive = false;
	updateAnimation();
}

void PlayerEntity::updateAnimation()
{
	Vector2 facing = _facingHistory.top();
	if (!_isAlive) {
		static_cast<AnimatedSprite*>(_sprite)->playAnimation("player_death", false, true);
	}
	else if (facing == Vector2::up()) {
		static_cast<AnimatedSprite*>(_sprite)->playAnimation("player_down", true);
	}
	else if (facing == Vector2::left()) {
		static_cast<AnimatedSprite*>(_sprite)->playAnimation("player_left", true);
	}
	else if (facing == Vector2::down()) {
		static_cast<AnimatedSprite*>(_sprite)->playAnimation("player_up", true);
	}
	else if (facing == Vector2::right()) {
		static_cast<AnimatedSprite*>(_sprite)->playAnimation("player_right", true);
	}
}

void PlayerEntity::undo(int turn)
{
	_isAlive = true;

	DirectionalEntity::undo(turn);
	updateAnimation();
}

void PlayerEntity::reset()
{
	_isAlive = true;
	
	DirectionalEntity::reset();
	updateAnimation();
}

bool PlayerEntity::turnTowards(int turn, Vector2 direction) {
	
	// store top up here so we can use throughout without fear of modifying the stack and for speed, also for readability
	Vector2 playerFacingDirection = _facingHistory.top();
	Vector2 currentCoordinate = _tileHistory.top()->getCoordinate();

	Vector2 diagonalCoordinate = currentCoordinate + playerFacingDirection + direction;
	Entity* diagonalEntity = NULL;
	if (_level->isCoordinateInRange(diagonalCoordinate)) {
		Tile* diagonalTile = _level->getTile(diagonalCoordinate);
		if (diagonalTile->isBlocked(ENTITY_SWORD)) {
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
		if (adjacentTile->isBlocked(ENTITY_SWORD)) {
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

	_facingHistory.push(direction);
	_lastTurnTurned.push(turn);
	updateAnimation();
	return true;
}
