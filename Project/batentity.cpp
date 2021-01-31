#include "batentity.h"
#include "level.h"
#include "animatedsprite.h"
#include "tile.h"
#include "spiketile.h"

BatEntity::BatEntity(Level* level, Sprite* sprite, Tile* startTile) :
	Entity(ENTITY_BAT, level, sprite, startTile)
{}