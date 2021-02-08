#include "boxentity.h"
#include "animatedsprite.h"
#include "tile.h"
#include "spiketile.h"


BoxEntity::BoxEntity(Level* level, Sprite* sprite, Tile* startTile) :
	Entity(ENTITY_BOX, level, sprite, startTile)
{}


// TODO add an update funciton, check to see if A you're in the box_fall animation and B it is complete, then kill
void BoxEntity::kill(int turn)
{
	static_cast<AnimatedSprite*>(_sprite)->playAnimation("box_fall", false);
	// TODO add pending turns function
	Entity::kill(turn);
}

bool BoxEntity::canMove(Vector2 direction) const
{
	Tile* currentTile = _tileHistory.top();
	if (currentTile->getTileType() == TILE_SPIKE && static_cast<SpikeTile*>(currentTile)->isBlocked(ENTITY_BOX)) {
		return false;
	}
	return Entity::canMove(direction);
}

void BoxEntity::undo(int turn)
{
	if (!_isAlive && _lastTurnMoved.size() > 0 && _lastTurnMoved.top() >= turn) {
		static_cast<AnimatedSprite*>(_sprite)->jumpToFrame("box_fall", 0);
	}
	Entity::undo(turn);
}

void BoxEntity::reset()
{
	static_cast<AnimatedSprite*>(_sprite)->jumpToFrame("box_fall", 0);
	Entity::reset();
}
