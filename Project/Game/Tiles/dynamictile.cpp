#include "dynamictile.h"

DynamicTile::DynamicTile(TileType tileType, Sprite* sprite, glm::vec2 coordinate, glm::vec2 position, int startingStage) :
	Tile(tileType, sprite, coordinate, position)
{
	_stageHistory.push(startingStage);
}

void DynamicTile::undo(int turn)
{
	if (_lastTurnModified.size() > 0 && _lastTurnModified.top() >= turn) {
		_lastTurnModified.pop();
		_stageHistory.pop();
	}
}

void DynamicTile::reset()
{
	while (_lastTurnModified.size() > 0) {
		_lastTurnModified.pop();
		_stageHistory.pop();
	}
}
