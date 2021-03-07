#pragma once
#include "globals.h"
#include "tile.h"
#include <vector>

class Level;
class SpikeTile;

class SwitchTile : public Tile
{
public:
	SwitchTile(Sprite* sprite, glm::vec2 coordinate, glm::vec2 position, bool blocked = false);
	void findAllSpikeTiles(Level* level);
protected:
	void onOccupy(int turn, EntityType outgoing = ENTITY_NONE) override;
	void onVacate(int turn, EntityType incoming = ENTITY_NONE) override;
private:
	std::vector<SpikeTile*> _spikeTiles;
};

