#include "boxentity.h"
#include "animatedsprite.h"
#include "tile.h"
#include "spiketile.h"


BoxEntity::BoxEntity(Level* level, Sprite* sprite, Tile* startTile) :
	Entity(ENTITY_BOX, level, sprite, startTile)
{
	_fallenTurn = 0;
}

void BoxEntity::fall(int turn)
{
	static_cast<AnimatedSprite*>(_sprite)->playAnimation("box_fall", false);
	_fallenTurn = turn;
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
	if (turn <= _fallenTurn) {
		static_cast<AnimatedSprite*>(_sprite)->jumpToFrame("box_fall", 0);
	}
	Entity::undo(turn);
}

void BoxEntity::reset()
{
	static_cast<AnimatedSprite*>(_sprite)->jumpToFrame("box_fall", 0);
	Entity::reset();
}
