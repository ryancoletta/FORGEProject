#pragma once
#include "tile.h"
#include <vector>
#include <string>
#include <map>
#include "sprite.h"
#include "tinyxml2.h"


class Level
{
public:
	Level();
	Level(int rows, int cols, Sprite* sprite);
	Level(Graphics* graphics, std::string levelPath);

	bool isCoordinateInRange(int x, int y);
	bool isCoordinateInRange(Vector2 coordinate);
	Tile* getTile(int x, int y);
	Tile* getTile(Vector2 coordinate);
	void draw();
	void loadMap(Graphics* graphics, std::string levelPath);
	void loadSpriteSheets(Graphics* graphics, tinyxml2::XMLElement* mapNode);
	std::string getSpriteSheet(int gid);
private:
	
	Sprite* _sprite; // TODO delete

	std::map<int, std::string> _spriteSheets; // first gid >> spriteSheet

	int _rows;
	int _cols;
	std::vector<std::vector<Tile>> _tiles;

};

