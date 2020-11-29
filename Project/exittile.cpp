#include "exittile.h"
#include <string>
#include "entity.h"
#include "game.h"

ExitTile::ExitTile() :
	_game(NULL)
{}

ExitTile::ExitTile(Game* game, Sprite* sprite, Vector2 coordinate, Vector2 position) :
	Tile(sprite, coordinate, position),
	_game(game)
{}

void ExitTile::onOccupy() {
	if (_occupant->getEntityID() == ENTITY_PLAYER) {
		_game->nextLevel();
	}
}