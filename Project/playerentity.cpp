#include "globals.h"
#include "playerentity.h"

PlayerEntity::PlayerEntity(EntityType entityID, Level* level, Sprite* sprite, Tile* startTile) :
	Entity(entityID, level, sprite, startTile)
{
	updateFlock();
}

bool PlayerEntity::move(int turn, Vector2 direction) {
	bool moved = Entity::canMove(direction);
	if (moved) {
		sortFlock(direction);
		for (int i = 0; i < _flock.size(); i++) {
			_flock[i]->Entity::move(turn, direction);
		}
		updateFlock();
	}
	return moved;
}

void PlayerEntity::updateFlock() {
	_flock.clear();
	getAllConnected(_flock, ENTITY_PLAYER | ENTITY_CHICKEN);
}

void PlayerEntity::sortFlock(Vector2 direction) {
	for (int i = 0; i < _flock.size() - 1; i++) {
		for (int j = 0; j < _flock.size() - i - 1; j++) {
			Vector2 coord1 = _flock[j]->getCoordinate();
			Vector2 coord2 = _flock[j + 1]->getCoordinate();

			// determine whichever is in the greater direction
			bool shouldSwap = false;
			if (direction == Vector2::up()) {
				shouldSwap = coord1.y < coord2.y;
			}
			else if (direction == Vector2::right()) {
				shouldSwap = coord1.x < coord2.x;
			}
			else if (direction == Vector2::down()) {
				shouldSwap = coord1.y > coord2.y;
			}
			else if (direction == Vector2::left()) {
				shouldSwap = coord1.x > coord2.x;
			}



			if (shouldSwap) {
				Entity* temp = _flock[j];
				_flock[j] = _flock[j + 1];
				_flock[j + 1] = temp;
			}
		}
	}
}