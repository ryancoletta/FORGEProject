#include "globals.h"
#include "tile.h"
#include "SDL.h"
#include "sprite.h"

Tile::Tile(TileType tileType, Sprite* sprite, Vector2 coordinate, Vector2 position, bool blocked) :
	_tileType(tileType),
	_sprite(sprite), 
	_coordinate(coordinate), 
	_position(position),
	_occupant(nullptr),
	_blocked(blocked)
{}

bool Tile::isBlocked(EntityType entrant) const { return _blocked; }
bool Tile::isOccupied() const { return _occupant != nullptr; }

TileType Tile::getTileType() const { return _tileType; }
Vector2 Tile::getCoordinate() const { return _coordinate; }
Vector2 Tile::getPosition() const { return _position; }
Sprite* Tile::getSprite() const { return _sprite; }
Entity* Tile::getOccupant() const { return _occupant; }

void Tile::setBlocked(bool blocked) { _blocked = blocked; }

void Tile::vacate(int turn, Entity* incoming) {
	onVacate(turn);
	_occupant = nullptr;
}
void Tile::occupy(Entity* entityToOccupy, int turn, Entity* outgoing) {
	_occupant = entityToOccupy; 
	onOccupy(turn);
}
void Tile::onVacate(int turn, Entity* incoming) { }
void Tile::onOccupy(int turn, Entity* outgoing) { }
void Tile::draw() { _sprite->draw(_position); }

void Tile::update(int deltaTimeMs) { _sprite->update(deltaTimeMs); }

