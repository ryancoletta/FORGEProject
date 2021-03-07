#include "directionalentity.h"
#include "Sprites/sprite.h"
#include "Tiles/tile.h"

DirectionalEntity::DirectionalEntity(EntityType entityID, Level* level, Sprite* sprite, Tile* startTile, glm::vec2 facing) :
	Entity(entityID, level, sprite, startTile)
{
	_facingHistory.push(facing);
}

glm::vec2 DirectionalEntity::getDirectionFacing() {
	return _facingHistory.top();
}

/*
void DirectionalEntity::draw() {
	float rotationalOffset = glm::vec2::angle(glm::vec2::up(), getDirectionFacing());
	_sprite->draw(_tileHistory.top()->getPosition(), rotationalOffset);
}
*/

void DirectionalEntity::undo(int turn) {
	while (_lastTurnTurned.size() > 0 && _lastTurnTurned.top() >= turn) {
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