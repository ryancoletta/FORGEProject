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

// maps gids to specific game elements (tiles, entities, sprites, etc)
enum GidElement {
	GID_TILE_WALL_END = 13,
	GID_TILE_OPEN_END = 14,
	GID_TILE_GOAL = 15,
	GID_ENTITY_BOX = 21,
	GID_ENTITY_CHICKEN = 22,
	GID_ENTITY_NAIL_HEAD = 24,
	GID_ENTITY_NAIL_BODY = 25,
	GID_ENTITY_NAIL_TAIL = 26,
	GID_ENTITY_PLAYER = 33,
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
	int getGidRotation(unsigned &gid);

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

