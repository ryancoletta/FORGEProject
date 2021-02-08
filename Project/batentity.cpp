#include "batentity.h"
#include "level.h"
#include "animatedsprite.h"
#include "tile.h"
#include "spiketile.h"

BatEntity::BatEntity(Level* level, Sprite* sprite, Tile* startTile) :
	Entity(ENTITY_BAT, level, sprite, startTile)
{}

void BatEntity::kill(int turn)
{
	static_cast<AnimatedSprite*>(_sprite)->playAnimation("bat_crushed", false, true);

	Entity::kill(turn);
}

void BatEntity::undo(int turn)
{
	if (!_isAlive && _lastTurnMoved.size() > 0 && _lastTurnMoved.top() >= turn) {
		static_cast<AnimatedSprite*>(_sprite)->playAnimation("bat_idle", true, true);
	}
	Entity::undo(turn);
}

void BatEntity::reset()
{
	static_cast<AnimatedSprite*>(_sprite)->playAnimation("bat_idle", true, true);
	Entity::reset();
}
