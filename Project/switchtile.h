#pragma once
#include "globals.h"
#include "tile.h"
#include <vector>

class Level;
class SpikeTile;

class SwitchTile : public Tile
{
public:
	SwitchTile(Sprite* sprite, Vector2 coordinate, Vector2 position, bool blocked = false);
	void findAllSpikeTiles(Level* level);
protected:
	void onOccupy() override;
	void onVacate() override;
private:
	std::vector<SpikeTile*> _spikeTiles;
};

