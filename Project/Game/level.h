#pragma once
#include "globals.h"
#include <vector>
#include <string>
#include <map>
#include "Tiles/tile.h"
#include <memory>
#include "tinyxml2.h"

class LevelManager;
class EntityManager;
class SpriteManager;
class Graphics;
struct SpriteSheet;

// maps gids to specific game elements (tiles, entities, sprites, etc)
enum GidElement {
	GID_TILE_WALL_END			= 42,
	GID_TILE_OPEN_END			= 59,
	GID_TILE_SWITCH				= 60,
	GID_TILE_HOLE				= 63,
	GID_TILE_GOAL				= 65,
	GID_TILE_SPIKE_OFF			= 66,
	GID_TILE_SPIKE_ON			= 69,
	GID_ENTITY_BOX				= 83,
	GID_ENTITY_BAT				= 107,
	GID_ENTITY_PLAYER_DOWN		= 195,
	GID_ENTITY_PLAYER_LEFT		= 207,
	GID_ENTITY_PLAYER_UP		= 219,
	GID_ENTITY_PLAYER_RIGHT		= 231,
};


class Level
{
public:
	Level(LevelManager* levelManager, Graphics* graphics, const std::string* levelPath, EntityManager* entityManager, SpriteManager* spriteManager);
	~Level();

	Tile* getTile(int x, int y) const;
	Tile* getTile(glm::vec2 coordinate) const;
	bool isCoordinateInRange(int x, int y) const;
	bool isCoordinateInRange(glm::vec2 coordinate) const;
	glm::vec2 getLevelSize() const;

	void loadMap(LevelManager* levelManager, Graphics* graphics, const std::string* levelPath);
	void loadSpriteSheets(Graphics* graphics, tinyxml2::XMLElement* mapNode);
	void draw();
	void update(int deltaTimeMs);
	void undo(int turn);
	void reset();

	int getGidRotation(unsigned &gid);
	void connectTiles();

private:
	glm::vec2 _levelSize;
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

