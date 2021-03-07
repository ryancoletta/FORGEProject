#include "globals.h"
#include "tile.h"
#include "SDL.h"
#include "Entities/entity.h"
#include "Sprites/sprite.h"

Tile::Tile(TileType tileType, Sprite* sprite, glm::vec2 coordinate, glm::vec2 position, bool blocked) :
	_tileType(tileType),
	_sprite(sprite), 
	_coordinate(coordinate), 
	_position(position),
	_blocked(blocked)
{}

bool Tile::isBlocked(EntityType entrant) const { return _blocked; }
bool Tile::isOccupied() const { 
	if (!_occupant.empty()) {
		return _occupant.top()->isAlive();
	}
	return false;
}

TileType Tile::getTileType() const { return _tileType; }
glm::vec2 Tile::getCoordinate() const { return _coordinate; }
glm::vec2 Tile::getPosition() const { return _position; }
Sprite* Tile::getSprite() const { return _sprite; }
Entity* Tile::getOccupant() const { 
	if (!_occupant.empty()) {
		return _occupant.top();
	}
	return nullptr;
}

void Tile::setBlocked(bool blocked) { _blocked = blocked; }

void Tile::vacate(int turn, EntityType incoming) {
	if (incoming != ENTITY_NULL) {
		onVacate(turn, incoming);
	}

	assert(!_occupant.empty());

	_occupant.pop();
}
void Tile::occupy(Entity* entityToOccupy, int turn, EntityType outgoing) {
	_occupant.push(entityToOccupy); 
	if (outgoing != ENTITY_NULL) {
		onOccupy(turn, outgoing);
	}
}
void Tile::onVacate(int turn, EntityType incoming) { }
void Tile::onOccupy(int turn, EntityType outgoing) { }
void Tile::draw() { _sprite->draw(_position); }

void Tile::update(int deltaTimeMs) { _sprite->update(deltaTimeMs); }

