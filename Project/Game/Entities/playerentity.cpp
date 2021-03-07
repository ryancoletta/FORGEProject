#include "globals.h"
#include "level.h"
#include "Tiles/tile.h"
#include "playerentity.h"
#include "Sprites/animatedsprite.h"

PlayerEntity::PlayerEntity(EntityType entityID, Level* level, Sprite* sprite, Tile* startTile, glm::vec2 facing) :
	DirectionalEntity(entityID, level, sprite, startTile, facing)
{
	updateAnimation();
}

bool PlayerEntity::move(int turn, glm::vec2 direction, EntityType pushingEntityType) {
	int dot = glm::dot(direction, _facingHistory.top());
	switch (dot) {
		// move to the right or left
		case 0:
			return turnTowards(turn, direction);
		// move forward
		case 1: {
			// first check if player can move
			if (!canMove(direction)) {
				return false;
			}

			// then check if sword can move
			glm::vec2 aheadCoordinate = _tileHistory.top()->getCoordinate() + glm::vec2(direction.x * 2, direction.y * 2);
			Tile* aheadTile = _level->getTile(aheadCoordinate);
			if (aheadTile->isBlocked(ENTITY_SWORD)) {
				return false;
			}
			else if (aheadTile->isOccupied()) {
				Entity* toPush = aheadTile->getOccupant();
				if (!toPush->canMove(direction)) {
					if ((toPush->getEntityType() & ENTITY_VULNERABLE) > 0) {
						toPush->kill(turn);
					}
					else return false;
				}
				toPush->move(turn, direction, ENTITY_SWORD);
				return Entity::move(turn, direction, pushingEntityType);
			}
		}
		// move backward
		default: {
			if (!canMove(direction)) {
				return false;
			}

			return Entity::move(turn, direction, pushingEntityType);
		}
	}
}

void PlayerEntity::kill(int turn)
{
	Entity::kill(turn);
	_sprite->setSortingOrder(1); // unlike other deaths, we DONT want the player sprite sorted to the bottom
	updateAnimation();
}

void PlayerEntity::updateAnimation()
{
	glm::vec2 facing = _facingHistory.top();
	if (!_isAlive) {
		static_cast<AnimatedSprite*>(_sprite)->playAnimation("player_death", false, true);
	}
	else if (facing == glm::vec2(0,1)) {
		static_cast<AnimatedSprite*>(_sprite)->playAnimation("player_down", true);
	}
	else if (facing == glm::vec2(-1,0)) {
		static_cast<AnimatedSprite*>(_sprite)->playAnimation("player_left", true);
	}
	else if (facing == glm::vec2(0,-1)) {
		static_cast<AnimatedSprite*>(_sprite)->playAnimation("player_up", true);
	}
	else if (facing == glm::vec2(1,0)) {
		static_cast<AnimatedSprite*>(_sprite)->playAnimation("player_right", true);
	}
}

void PlayerEntity::undo(int turn)
{
	DirectionalEntity::undo(turn);
	updateAnimation();
}

void PlayerEntity::reset()
{	
	DirectionalEntity::reset();
	updateAnimation();
}

bool PlayerEntity::turnTowards(int turn, glm::vec2 direction) {
	
	// store top up here so we can use throughout without fear of modifying the stack and for speed, also for readability
	glm::vec2 playerFacingDirection = _facingHistory.top();
	glm::vec2 currentCoordinate = _tileHistory.top()->getCoordinate();

	glm::vec2 diagonalCoordinate = currentCoordinate + playerFacingDirection + direction;
	Entity* diagonalEntity = nullptr;
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

	glm::vec2 adjacentCoordinate = currentCoordinate + direction;
	Entity* adjacentEntity = nullptr;
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
