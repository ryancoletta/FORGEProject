#include "spiketile.h"
#include "entity.h"
#include "animatedsprite.h"
#include "playerentity.h"
SpikeTile::SpikeTile(Sprite* sprite, Vector2 coordinate, Vector2 position, bool isOn) :
	Tile(TILE_SPIKE, sprite, coordinate, position),
	_isOn(isOn)
{}

void SpikeTile::toggleSpikes(int turn)
{
	_isOn = !_isOn;
	static_cast<AnimatedSprite*>(_sprite)->playAnimation("spikes_on", false, true, !_isOn);
	_lastTurnToggled.push(turn);
	tryHurtOccupant();
}

void SpikeTile::undo(int turn)
{
	if (_lastTurnToggled.size() > 0 && _lastTurnToggled.top() >= turn) {
		_lastTurnToggled.pop();
		_isOn = !_isOn;
	}
	static_cast<AnimatedSprite*>(_sprite)->jumpToFrame("spikes_on", _isOn ? 3 : 0);
}

void SpikeTile::reset()
{
	while (_lastTurnToggled.size() > 0) {
		_lastTurnToggled.pop();
		_isOn = !_isOn;
	}
	static_cast<AnimatedSprite*>(_sprite)->jumpToFrame("spikes_on", _isOn ? 3 : 0);
}

void SpikeTile::onOccupy(int turn)
{
	tryHurtOccupant();
}

void SpikeTile::tryHurtOccupant()
{
	if (_isOn && _occupant && _occupant->getEntityType() == ENTITY_PLAYER) {
		static_cast<PlayerEntity*>(_occupant)->kill();
	}
}
