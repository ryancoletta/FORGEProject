#include "globals.h"
#include "exittile.h"
#include <string>
#include "Entities/entity.h"
#include "game.h"
#include "levelmanager.h"
#include "Sprites/sprite.h"

ExitTile::ExitTile(LevelManager* levelManager, Sprite* sprite, Vector2 coordinate, Vector2 position) :
	Tile(TILE_GOAL, sprite, coordinate, position),
	_levelManager(levelManager)
{}

void ExitTile::onOccupy(int turn, EntityType outgoing) {
	if (_occupant.top()->getEntityType() == ENTITY_PLAYER) {
		_levelManager->levelComplete();
	}
}