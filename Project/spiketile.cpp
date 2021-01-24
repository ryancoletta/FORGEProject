#include "spiketile.h"
#include "entity.h"
#include "animatedsprite.h"
#include "playerentity.h"
SpikeTile::SpikeTile(Sprite* sprite, Vector2 coordinate, Vector2 position, bool isOn) :
	Tile(TILE_SPIKE, sprite, coordinate, position),
	_isOn(isOn)
{}

void SpikeTile::toggleSpikes()
{
	_isOn = !_isOn;
	static_cast<AnimatedSprite*>(_sprite)->playAnimation("spikes_on", false, true, !_isOn);
	tryHurtOccupant();
}

void SpikeTile::onOccupy()
{
	tryHurtOccupant();
}

void SpikeTile::tryHurtOccupant()
{
	if (_isOn && _occupant && _occupant->getEntityType() == ENTITY_PLAYER) {
		static_cast<PlayerEntity*>(_occupant)->kill();
	}
}
