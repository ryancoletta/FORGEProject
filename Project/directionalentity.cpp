#include "directionalentity.h"
#include "sprite.h"
#include "tile.h"

DirectionalEntity::DirectionalEntity(EntityType entityID, Level* level, Sprite* sprite, Tile* startTile, Vector2 facing) :
	Entity(entityID, level, sprite, startTile)
{
	_facingHistory.push(facing);
}

Vector2 DirectionalEntity::getDirectionFacing() {
	return _facingHistory.top();
}

void DirectionalEntity::draw() {
	float rotationalOffset = Vector2::angle(Vector2::up(), getDirectionFacing());
	_sprite->draw(_tileHistory.top()->getPosition(), rotationalOffset);
}

void DirectionalEntity::undo(int turn) {
	while (_facingHistory.size() > 1 && _lastTurnTurned.top() >= turn) {
		_facingHistory.pop();
		_lastTurnTurned.pop();
	}
	Entity::undo(turn);
}

void DirectionalEntity::reset() {
	while (_lastTurnTurned.size() > 0) {
		_facingHistory.pop();
		_lastTurnTurned.pop();
	}
	Entity::reset();
}