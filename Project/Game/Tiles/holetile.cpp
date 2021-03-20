#include "holetile.h"
#include "Sprites/sprite.h"
#include "Entities/entity.h"
#include "Sprites/animatedsprite.h".
#include "Entities/boxentity.h"
#include "soundmanager.h"

HoleTile::HoleTile(Sprite* sprite, glm::vec2 coordinate, glm::vec2 position) :
	DynamicTile(TILE_HOLE, sprite, coordinate, position, 0)
{}

void HoleTile::onOccupy(int turn, EntityType outgoing)
{
	if (_stageHistory.top() == 0 && _occupant.top()->getEntityType() == ENTITY_BOX) {
		_occupant.top()->kill(turn);
		_stageHistory.push(1);
		_lastTurnModified.push(turn);
		SoundManager::instance->PlaySFX("fall");
	}
}

bool HoleTile::isBlocked(EntityType entrant) const
{
	return _stageHistory.top() != 1 && entrant == ENTITY_PLAYER;
}