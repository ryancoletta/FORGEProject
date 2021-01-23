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
	GID_TILE_WALL_END = 23,
	GID_TILE_OPEN_END = 39,
	GID_TILE_GOAL = 44,
	GID_TILE_SWITCH = 40,
	GID_TILE_SPIKE_OFF = 45,
	GID_TILE_SPIKE_ON = 48,
	GID_ENTITY_BOX = 90,
	GID_ENTITY_PLAYER = 140,
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
	Vector2 getLevelSize() const;

	void loadMap(LevelManager* levelManager, Graphics* graphics, const std::string* levelPath);
	void loadSpriteSheets(Graphics* graphics, tinyxml2::XMLElement* mapNode);
	void draw();
	void update(int deltaTimeMs);
	int getGidRotation(unsigned &gid);
	void connectTiles();

private:
	Vector2 _levelSize;
	EntityManager* _entityManager;
	SpriteManager* _spriteManager;
	std::vector<std::vector<Tile*>> _tiles;
	std::vector<SpriteSheet> _spriteSheets;
};

struct SpriteSheet {
	int firstGid;
	int width, height;
	std::string path;
	SpriteSheet() {
		this->firstGid = 0;
		this->path = "";
	}
 	SpriteSheet(int firstGid, int width, int height, std::string path) {
		this->firstGid = firstGid;
		this->width = width;
		this->height = height;
		this->path = path;
	}
};

