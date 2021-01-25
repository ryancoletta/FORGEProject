#include "crackedtile.h"
#include "sprite.h"
#include "entity.h"
#include "animatedsprite.h".
#include "boxentity.h"

CrackedTile::CrackedTile(int progress, Sprite* sprite, Vector2 coordinate, Vector2 position) :
	Tile(TILE_CRACKED, sprite, coordinate, position),
	_crackProgress(progress)
{}

void CrackedTile::onOccupy(int turn)
{
	if (_occupant->getEntityType() == ENTITY_BOX && _crackProgress == 2) {
		static_cast<BoxEntity*>(_occupant)->fall(turn);
	}
}

void CrackedTile::onVacate(int turn)
{
	if (_occupant->getEntityType() == ENTITY_SWORD) { return; }
	_crackProgress++;
	_lastTurnCracked.push(turn);
	static_cast<AnimatedSprite*>(_sprite)->jumpToFrame("tile_crack", _crackProgress);
}

bool CrackedTile::isBlocked(EntityType entrant) const
{
	return entrant == ENTITY_PLAYER && _crackProgress == 2;
}

void CrackedTile::undo(int turn)
{
	if (_lastTurnCracked.size() > 0 && _lastTurnCracked.top() >= turn) {
		_lastTurnCracked.pop();
		_crackProgress--;
	}
	static_cast<AnimatedSprite*>(_sprite)->jumpToFrame("tile_crack", _crackProgress);
}

void CrackedTile::reset()
{
	while (_lastTurnCracked.size() > 0) {
		_lastTurnCracked.pop();
		_crackProgress--;
	}
	static_cast<AnimatedSprite*>(_sprite)->jumpToFrame("tile_crack", _crackProgress);
}


