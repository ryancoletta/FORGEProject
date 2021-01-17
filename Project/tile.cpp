#include "globals.h"
#include "tile.h"
#include "SDL.h"
#include "sprite.h"

Tile::Tile(TileType tileType, Sprite* sprite, Vector2 coordinate, Vector2 position, bool blocked) :
	_tileType(tileType),
	_sprite(sprite), 
	_coordinate(coordinate), 
	_position(position),
	_occupant(NULL),
	_blocked(blocked)
{}

bool Tile::isBlocked() const { return _blocked; }
bool Tile::isOccupied() const { return _occupant != NULL; }

TileType Tile::getTileType() const { return _tileType; }
Vector2 Tile::getCoordinate() const { return _coordinate; }
Vector2 Tile::getPosition() const { return _position; }
Sprite* Tile::getSprite() const { return _sprite; }
Entity* Tile::getOccupant() const { return _occupant; }

void Tile::setBlocked(bool blocked) { _blocked = blocked; }

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

