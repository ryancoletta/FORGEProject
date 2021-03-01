#include "holetile.h"
#include "sprite.h"
#include "entity.h"
#include "animatedsprite.h".
#include "boxentity.h"

HoleTile::HoleTile(Sprite* sprite, Vector2 coordinate, Vector2 position) :
	DynamicTile(TILE_HOLE, sprite, coordinate, position, 0)
{}

void HoleTile::onOccupy(int turn, Entity* outgoing)
{
	if (_stageHistory.top() == 0 && _occupant->getEntityType() == ENTITY_BOX) {
		_occupant->kill(turn);
		_stageHistory.push(1);
		_lastTurnModified.push(turn);
	}
}

bool HoleTile::isBlocked(EntityType entrant) const
{
	return _stageHistory.top() != 1 && entrant == ENTITY_PLAYER;
}