#pragma once

#include <vector>
#include <string>
#include <map>
#include "tile.h"
#include <memory>
#include "tinyxml2.h"

class Game;
class EntityManager;
class SpriteManager;
class Graphics;
struct SpriteSheet;

class Level
{
public:
	Level();
	Level(Game* game, Graphics* graphics, std::string levelPath, EntityManager* entityManager, SpriteManager* spriteManager);
	~Level();
	bool isCoordinateInRange(int x, int y);
	bool isCoordinateInRange(Vector2 coordinate);
	Tile* getTile(int x, int y);
	Tile* getTile(Vector2 coordinate);
	void draw();
	void loadMap(Game* game, Graphics* graphics, std::string levelPath);
	void loadSpriteSheets(Graphics* graphics, tinyxml2::XMLElement* mapNode);
private:
	EntityManager* _entityManager;
	SpriteManager* _spriteManager;
	int _rows;
	int _cols;
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

