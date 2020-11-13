#include "grid.h"

Grid::Grid() {

}

Grid::Grid(int rows, int cols) : _rows(rows), _cols(cols) {

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
			Tile tile(tileCoordinate, windowCenter - totalScale / 2 + tilePosition);
			row[y] = tile;
		}
		_tiles[x] = row;
	}
}
bool Grid::isCoordinateInRange(int x, int y) {
	return (x >= 0) && (y >= 0) && (x < _cols) && (y < _rows);
}
bool Grid::isCoordinateInRange(Vector2 coordinate) {
	return isCoordinateInRange(coordinate.x, coordinate.y);
}

Tile Grid::getTile(int x, int y) {
	return _tiles[x][y]; // TODO error where this works when these are SWAPED
}
Tile Grid::getTile(Vector2 coordinate) {
	return getTile(coordinate.x, coordinate.y);
}
