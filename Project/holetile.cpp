#include "holetile.h"
#include "sprite.h"
#include "entity.h"
#include "animatedsprite.h".
#include "boxentity.h"

HoleTile::HoleTile(Sprite* sprite, Vector2 coordinate, Vector2 position) :
	Tile(TILE_HOLE, sprite, coordinate, position)
{}

void HoleTile::onOccupy(int turn)
{
	if (_occupant->getEntityType() == ENTITY_BOX) {
		_occupant->kill(turn);
	}
}

bool HoleTile::isBlocked(EntityType entrant) const
{
	return entrant == ENTITY_PLAYER;
}


