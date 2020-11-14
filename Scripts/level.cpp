#include "level.h"

Level::Level() :
	_rows(0),
	_cols(0),
	_sprite(NULL)
{}

Level::Level(int rows, int cols, Sprite* sprite) : 
	_rows(rows), 
	_cols(cols), 
	_sprite(sprite) 
{
	// center the tiles to the window
	Vector2 windowCenter = Vector2(globals::WINDOW_WIDTH / 2, globals::WINDOW_HEIGHT / 2);
	int cellSize = 16 * globals::SPRITE_SCALE;
	Vector2 totalScale = Vector2(rows * cellSize, cols * cellSize);

	_tiles.resize(rows);
	for (int x = 0; x < cols; x++) {
		std::vector<Tile> row;
		row.resize(cols);
		for (int y = 0; y < rows; y++) {
			Vector2 tileCoordinate(x, y);
			Vector2 tilePosition(x * cellSize, y * cellSize);
			Tile tile(_sprite, tileCoordinate, windowCenter - totalScale / 2 + tilePosition);
			row[y] = tile;
		}
		_tiles[x] = row;
	}
}
bool Level::isCoordinateInRange(int x, int y) {
	return (x >= 0) && (y >= 0) && (x < _cols) && (y < _rows);
}
bool Level::isCoordinateInRange(Vector2 coordinate) {
	return isCoordinateInRange(coordinate.x, coordinate.y);
}

Tile* Level::getTile(int x, int y) {
	return &_tiles[x][y]; // TODO error where this works when these are SWAPED
}
Tile* Level::getTile(Vector2 coordinate) {
	return getTile(coordinate.x, coordinate.y);
}

void Level::draw() {
	for (int x = 0; x < _tiles.size(); x++) {
		for (int y = 0; y < _tiles[x].size(); y++) {
			_tiles[x][y].draw();
		}
	}
}
