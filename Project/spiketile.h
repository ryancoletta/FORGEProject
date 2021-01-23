#pragma once
#include "tile.h"
class SpikeTile : public Tile
{
public:
	SpikeTile(Sprite* sprite, Vector2 coordinate, Vector2 position, bool isOn);
	void toggleSpikes();
protected:
	void onOccupy() override;
private:
	bool _isOn;
};

