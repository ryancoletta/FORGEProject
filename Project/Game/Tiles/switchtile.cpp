#include "switchtile.h"
#include "level.h"
#include "spiketile.h"
#include "Entities/entity.h"
#include "soundmanager.h"

SwitchTile::SwitchTile(Sprite* sprite, glm::vec2 coordinate, glm::vec2 position, bool blocked) :
	Tile(TILE_SWITCH, sprite, coordinate, position)
{}

void SwitchTile::findAllSpikeTiles(Level* level)
{
	glm::vec2 levelSize = level->getLevelSize();
	for (int x = 0; x < levelSize.x; x++) {
		for (int y = 0; y < levelSize.y; y++) {
			SpikeTile* tile = static_cast<SpikeTile*>(level->getTile(x, y));
			if (tile && tile->getTileType() == TILE_SPIKE) {
				_spikeTiles.push_back(tile);
			}
		}
	}
}

void SwitchTile::onOccupy(int turn, EntityType outgoing)
{
	bool isIncomingGrounded = (_occupant.top()->getEntityType() & ENTITY_GROUNDED) > 0;
	bool isOutgoingGrounded = (outgoing & ENTITY_GROUNDED) > 0;
	if (isIncomingGrounded ^ isOutgoingGrounded) {
		SoundManager::instance->PlaySFX("button");
		for (int i = 0; i < _spikeTiles.size(); i++) {
			_spikeTiles[i]->toggleSpikes(turn);
		}
	}
}

void SwitchTile::onVacate(int turn, EntityType incoming)
{
	bool isIncomingGrounded = (incoming & ENTITY_GROUNDED) > 0; 
	bool isOutgoingGrounded = (_occupant.top()->getEntityType() & ENTITY_GROUNDED) > 0;
	if (isIncomingGrounded ^ isOutgoingGrounded) {
		SoundManager::instance->PlaySFX("button");
		for (int i = 0; i < _spikeTiles.size(); i++) {
			_spikeTiles[i]->toggleSpikes(turn);
		}
	}
}

