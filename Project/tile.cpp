#include "tile.h"
#include "SDL.h"
#include "sprite.h"

Tile::Tile() :
	_sprite(NULL),
	_coordinate(Vector2::zero()),
	_position(Vector2::zero()),
	_occupant(NULL),
	_blocked(false)
{}
Tile::Tile(Sprite* sprite, Vector2 coordinate, Vector2 position, bool blocked) : 
	_sprite(sprite), 
	_coordinate(coordinate), 
	_position(position),
	_occupant(NULL),
	_blocked(blocked)
{}
Tile::~Tile() {}
void Tile::setBlocked(bool blocked) { _blocked = blocked; }
bool Tile::isBlocked() { return _blocked; }
Vector2 Tile::getCoordinate() { return _coordinate; }
Vector2 Tile::getPosition() { return _position; }
Sprite* Tile::getSprite() { return _sprite; }
Entity* Tile::getOccupant() { return _occupant; }
bool Tile::isOccupied() { return _occupant != NULL; }
void Tile::vacate() { 
	_occupant = NULL;
	onVacate();
}
void Tile::occupy(Entity* entityToOccupy) { 
	_occupant = entityToOccupy; 
	onOccupy();
}
void Tile::onVacate() { }
void Tile::onOccupy() { }
void Tile::draw() { _sprite->draw(_position); }

