#include "tile.h"
#include "SDL.h"

Tile::Tile() {}
Tile::Tile(Vector2 coordinate, Vector2 position) : _coordinate(coordinate), _position(position) { }
Vector2 Tile::getCoordinate() { return _coordinate; }
Vector2 Tile::getPosition() { return _position; }
