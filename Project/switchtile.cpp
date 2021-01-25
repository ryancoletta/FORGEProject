#include "switchtile.h"
#include "level.h"
#include "spiketile.h"

SwitchTile::SwitchTile(Sprite* sprite, Vector2 coordinate, Vector2 position, bool blocked) :
	Tile(TILE_SWITCH, sprite, coordinate, position)
{}

void SwitchTile::findAllSpikeTiles(Level* level)
{
	Vector2 levelSize = level->getLevelSize();
	for (int x = 0; x < levelSize.x; x++) {
		for (int y = 0; y < levelSize.y; y++) {
			SpikeTile* tile = static_cast<SpikeTile*>(level->getTile(x, y));
			if (tile && tile->getTileType() == TILE_SPIKE) {
				_spikeTiles.push_back(tile);
			}
		}
	}
}

void SwitchTile::onOccupy(int turn)
{
	for (int i = 0; i < _spikeTiles.size(); i++) {
		_spikeTiles[i]->toggleSpikes(turn);
	}
}

void SwitchTile::onVacate(int turn)
{
	for (int i = 0; i < _spikeTiles.size(); i++) {
		_spikeTiles[i]->toggleSpikes(turn);
	}
}

