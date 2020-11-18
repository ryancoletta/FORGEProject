#include "tile.h"
#include "SDL.h"
#include "sprite.h"

Tile::Tile() :
	_sprite(NULL),
	_coordinate(Vector2::zero()),
	_position(Vector2::zero())
{}
Tile::Tile(Sprite* sprite, Vector2 coordinate, Vector2 position) : 
	_sprite(sprite), 
	_coordinate(coordinate), 
	_position(position) 
{}
Vector2 Tile::getCoordinate() { return _coordinate; }
Vector2 Tile::getPosition() { return _position; }
Sprite* Tile::getSprite() { return _sprite; }
void Tile::draw() {
	_sprite->draw(_position);
}