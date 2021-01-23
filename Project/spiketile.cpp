#include "spiketile.h"
#include "entity.h"
#include "animatedsprite.h"

SpikeTile::SpikeTile(Sprite* sprite, Vector2 coordinate, Vector2 position, bool isOn) :
	Tile(TILE_SPIKE, sprite, coordinate, position),
	_isOn(isOn)
{}

void SpikeTile::toggleSpikes()
{
	_isOn = !_isOn;
	static_cast<AnimatedSprite*>(_sprite)->playAnimation("spikes_on", false, true, !_isOn);
}

void SpikeTile::onOccupy()
{
	if (_isOn && _occupant->getEntityType() == ENTITY_PLAYER) {
		printf("OOF");
	}
}
