#pragma once
#include "globals.h"
#include <vector>
#include <string>
#include <map>
#include "tile.h"
#include <memory>
#include "tinyxml2.h"

class LevelManager;
class EntityManager;
class SpriteManager;
class Graphics;
struct SpriteSheet;

// defines gids which are supposed to create special elements
enum GidElement {
	GID_TILE_WALL_END = 13,
	GID_TILE_OPEN_END = 14,
	GID_TILE_GOAL = 15,
	GID_ENTITY_BOX = 21,
	GID_ENTITY_CHICKEN = 22,
	GID_ENTITY_PLAYER_UP = 42,
	GID_ENTITY_PLAYER_RIGHT = 45,
	GID_ENTITY_PLAYER_DOWN = 48,
	GID_ENTITY_PLAYER_LEFT = 51,
};


class Level
{
public:
	Level(LevelManager* levelManager, Graphics* graphics, const std::string* levelPath, EntityManager* entityManager, SpriteManager* spriteManager);
	~Level();

	Tile* getTile(int x, int y) const;
	Tile* getTile(Vector2 coordinate) const;
	bool isCoordinateInRange(int x, int y) const;
	bool isCoordinateInRange(Vector2 coordinate) const;

	void loadMap(LevelManager* levelManager, Graphics* graphics, const std::string* levelPath);
	void loadSpriteSheets(Graphics* graphics, tinyxml2::XMLElement* mapNode);
	void draw();

private:
	Vector2 _levelSize;
	EntityManager* _entityManager;
	SpriteManager* _spriteManager;
	std::vector<std::vector<Tile*>> _tiles;
	std::vector<SpriteSheet> _spriteSheets;
};

struct SpriteSheet {
	int firstGid;
	int width;
	std::string path;
	SpriteSheet() {
		this->firstGid = 0;
		this->path = "";
	}
 	SpriteSheet(int firstGid, int width, std::string path) {
		this->firstGid = firstGid;
		this->width = width;
		this->path = path;
	}
};

