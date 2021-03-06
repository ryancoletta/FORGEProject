#include "batentity.h"
#include "level.h"
#include "Sprites/animatedsprite.h"
#include "Tiles/tile.h"
#include "Tiles/spiketile.h"
#include "soundmanager.h"

BatEntity::BatEntity(Level* level, Sprite* sprite, Tile* startTile) :
	Entity(ENTITY_BAT, level, sprite, startTile)
{}

void BatEntity::kill(int turn)
{
	SoundManager::instance->PlaySFX("death");
	static_cast<AnimatedSprite*>(_sprite)->playAnimation("bat_crushed", false, true);

	Entity::kill(turn);
}

void BatEntity::undo(int turn)
{
	if (!_isAlive && _lastTurnMoved.size() > 0 && _lastTurnMoved.top() >= turn) {
		static_cast<AnimatedSprite*>(_sprite)->playAnimation("bat_idle", true);
	}
	Entity::undo(turn);
}

void BatEntity::reset()
{
	static_cast<AnimatedSprite*>(_sprite)->playAnimation("bat_idle", true);
	Entity::reset();
}
