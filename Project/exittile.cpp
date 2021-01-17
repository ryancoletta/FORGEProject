#include "globals.h"
#include "exittile.h"
#include <string>
#include "entity.h"
#include "game.h"
#include "levelmanager.h"
#include "spriteinstance.h"

ExitTile::ExitTile(LevelManager* levelManager, SpriteInstance* sprite, Vector2 coordinate, Vector2 position) :
	Tile(TILE_GOAL, sprite, coordinate, position),
	_levelManager(levelManager)
{}

void ExitTile::onOccupy() {
	if (_occupant->getEntityType() == ENTITY_PLAYER) {
		_levelManager->levelComplete();
	}
}