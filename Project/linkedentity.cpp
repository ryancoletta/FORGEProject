#include "linkedentity.h"
#include "tile.h"
#include "level.h"

LinkedEntity::LinkedEntity(EntityType entityID, Level* level, Sprite* sprite, Tile* startTile, Vector2 facing) :
	DirectionalEntity(entityID, level, sprite, startTile, facing) 
{}

// must start at the HEAD node
std::vector<LinkedEntity*> LinkedEntity::Link() {

	// TODO pick up on this
	// recursively add the next
	/*
	Vector2 facingDirection = _facingHistory.top();
	Vector2 nextCoordinate = _tileHistory.top()->getCoordinate() + facingDirection;
	if (_level->isCoordinateInRange(nextCoordinate)) {
		Tile* newTile = _level->getTile(nextCoordinate);
		if (newTile->isBlocked()) {
			// ???
		}
		else if (newTile->isOccupied()) {
			Entity* toLink = newTile->getOccupant();
			if (toLink->getEntityType() == ENTITY_NAIL) {
				static_cast<LinkedEntity*>(toLink)->Link();
			}
		}
	}
	// add self
	_allLinkedEntities.push_back(this);
	*/
	return _allLinkedEntities;
}

bool LinkedEntity::canMove(Vector2 direction) const {
	for (int i = 0; i < _allLinkedEntities.size(); i++) {
		if(!_allLinkedEntities[i]->Entity::canMove(direction)) {
			return false;
		}
	}
	return true;
}
bool LinkedEntity::move(int turn, Vector2 direction) {

	// must first reorder so whatever is in *direction* goes first

	for (int i = 0; i < _allLinkedEntities.size(); i++) {
		if (!_allLinkedEntities[i]->Entity::move(turn, direction)) {
			return false;
		}
	}
	return true;
}