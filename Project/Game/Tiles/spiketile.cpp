#include "spiketile.h"
#include "Entities/entity.h"
#include "Sprites/animatedsprite.h"
#include "Entities/playerentity.h"
SpikeTile::SpikeTile(Sprite* sprite, Vector2 coordinate, Vector2 position, int startingStage) :
	DynamicTile(TILE_SPIKE, sprite, coordinate, position, startingStage)
{}

void SpikeTile::toggleSpikes(int turn)
{
	int toggleStage = (_stageHistory.top() + 1) % 2;
	_stageHistory.push(toggleStage);
	static_cast<AnimatedSprite*>(_sprite)->playAnimation("spikes_on", false, true, !_stageHistory.top());
	_lastTurnModified.push(turn);
	tryHurtOccupant(turn);
}

void SpikeTile::undo(int turn)
{
	DynamicTile::undo(turn);
	static_cast<AnimatedSprite*>(_sprite)->jumpToFrame("spikes_on", _stageHistory.top() ? 3 : 0);
}

void SpikeTile::reset()
{
	DynamicTile::reset();
	static_cast<AnimatedSprite*>(_sprite)->jumpToFrame("spikes_on", _stageHistory.top() ? 3 : 0);
}

bool SpikeTile::isBlocked(EntityType entrant) const
{
	if (_stageHistory.top() && (entrant & ENTITY_GROUNDED) > 0) {
		return true;
	}
	return false;
}

void SpikeTile::onOccupy(int turn, Entity* outgoing)
{
	tryHurtOccupant(turn);
}

void SpikeTile::tryHurtOccupant(int turn)
{
	if (_stageHistory.top() && _occupant && _occupant->getEntityType() == ENTITY_PLAYER) {
		static_cast<PlayerEntity*>(_occupant)->kill(turn);
	}
}
