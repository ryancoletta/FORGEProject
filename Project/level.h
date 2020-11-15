#pragma once

#include <vector>
#include <string>
#include <map>
#include "tile.h"
#include <memory>
#include "tinyxml2.h"

class EntityManager;

class Level
{
public:
	Level();
	Level(Graphics* graphics, std::string levelPath, EntityManager* entityManager);

	bool isCoordinateInRange(int x, int y);
	bool isCoordinateInRange(Vector2 coordinate);
	Tile* getTile(int x, int y);
	Tile* getTile(Vector2 coordinate);
	void draw();
	void loadMap(Graphics* graphics, std::string levelPath);
	void loadSpriteSheets(Graphics* graphics, tinyxml2::XMLElement* mapNode);
	std::string getSpriteSheet(int gid);
private:
	std::map<int, std::string> _spriteSheets; // TODO idk what I was thinking, make this a struct called tileSet
	EntityManager* _entityManager;
	int _rows;
	int _cols;
	std::vector<std::vector<Tile>> _tiles;

};

