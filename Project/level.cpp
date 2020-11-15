#include "level.h"
#include <stdio.h>
#include <sstream>
#include <algorithm>
#include <cmath>
#include "entitymanager.h"
#include "sprite.h"
#include "entity.h"

using namespace tinyxml2;

Level::Level() :
	_rows(0),
	_cols(0)
{}
Level::Level(Graphics* graphics, std::string levelPath, EntityManager* entityManager) :
	_entityManager(entityManager)
{
	loadMap(graphics, levelPath);
}
bool Level::isCoordinateInRange(int x, int y) {
	return (x >= 0) && (y >= 0) && (x < _cols) && (y < _rows);
}
bool Level::isCoordinateInRange(Vector2 coordinate) {
	return isCoordinateInRange(coordinate.x, coordinate.y);
}
Tile* Level::getTile(int x, int y) {
	return &_tiles[x][y];
}
Tile* Level::getTile(Vector2 coordinate) {
	return getTile(coordinate.x, coordinate.y);
}
void Level::draw() {
	for (int x = 0; x < _tiles.size(); x++) {
		for (int y = 0; y < _tiles[x].size(); y++) {
			_tiles[x][y].draw();
		}
	}
}
void Level::loadMap(Graphics* graphics, std::string levelPath) {
	XMLDocument doc;
	std::stringstream ss;
	ss << levelPath;
	doc.LoadFile(ss.str().c_str());

	XMLElement* mapNode = doc.FirstChildElement("map");
	mapNode->QueryIntAttribute("width", &_cols);
	mapNode->QueryIntAttribute("height", &_rows);

	_tiles.resize(_cols);
	for (int x = 0; x < _cols; x++) {
		_tiles[x].resize(_rows);
	}

	int tileWidth, tileHeight;
	mapNode->QueryIntAttribute("tilewidth", &tileWidth);
	mapNode->QueryIntAttribute("tileheight", &tileHeight);
	Vector2 tileSize(tileWidth, tileHeight);

	loadSpriteSheets(graphics, mapNode);

	// TODO any way to make this less hideously nested
	XMLElement* pLayer = mapNode->FirstChildElement("layer");
	if (pLayer) {
		while (pLayer) {
			const char* layerName;
			pLayer->QueryStringAttribute("name", &layerName);
			XMLElement* pData = pLayer->FirstChildElement("data");
			if (pData) {
				while (pData) {
					XMLElement* pTile = pData->FirstChildElement("tile");
					int tileCounter = 0;
					if (pTile) {
						while (pTile) {

							int gid = pTile->IntAttribute("gid") - 1;
							
							// handle empty gids
							if (gid == -1) {
								tileCounter++;
								if (pTile->NextSiblingElement("tile")) {
									pTile = pTile->NextSiblingElement("tile");
									continue;
								}
								else {
									break;
								}
							}

							std::string spriteSheet = getSpriteSheet(gid);

							// handle spritesheets that don't exist
							if (spriteSheet == "") {
								tileCounter++;
								if (pTile->NextSiblingElement("tile")) {
									pTile = pTile->NextSiblingElement("tile");
									continue;
								}
								else {
									break;
								}
							}

							// get the position of tile in the level
							int x = tileCounter % _cols;
							int y = tileCounter / _cols;
							int posX = x * tileWidth * globals::SPRITE_SCALE;
							int posY = y * tileHeight * globals::SPRITE_SCALE;
							Vector2 finalTilePosition = Vector2(posX, posY);

							// calculate the position of the tile in the tileset
							int spriteSheetWidth = 48; // TODO hard coded, read from file
							int spriteSheetX = gid % (spriteSheetWidth / tileWidth);
							spriteSheetX *= tileWidth;
							int spriteSheetY = gid / (spriteSheetWidth / tileWidth);
							spriteSheetY *= tileHeight;
							Vector2 finalTilesetPosition = Vector2(spriteSheetX, spriteSheetY);

							// TODO this sprite is destroyed as soon as it exits this scope, cannot store as pointer on entity
							Sprite tileSprite(graphics, spriteSheet, finalTilesetPosition, tileSize, finalTilePosition);

							if (std::string(layerName) == "BG") {
								Tile tile(tileSprite, Vector2(x, y), finalTilePosition);
								_tiles[x][y] = tile;
							}
							else {
								// TODO this entity is destroyed as soon as it exits this scope, cannot store as a pointer on entitymanager
								Entity newEntity( this, &tileSprite, &_tiles[x][y]);
								//_entityManager->addEntity(&newEntity);
							}


							tileCounter++;

							pTile = pTile->NextSiblingElement("tile");
						}
					}
					pData = pData->NextSiblingElement("data");
				}
			}
			pLayer = pLayer->NextSiblingElement("layer");
		}
	}
}

void Level::loadSpriteSheets(Graphics* graphics, XMLElement* mapNode) {
	XMLElement* pSpriteSheet = mapNode->FirstChildElement("tileset");
	if (pSpriteSheet) {
		while (pSpriteSheet) {

			int firstGid;
			pSpriteSheet->QueryAttribute("firstgid", &firstGid);

			const char* source = pSpriteSheet->FirstChildElement("image")->Attribute("source");

			std::stringstream ss;
			ss << "Assets/" << source;
			_spriteSheets.insert(std::pair<int, std::string>(firstGid, ss.str()));

			pSpriteSheet = pSpriteSheet->NextSiblingElement("tileset");
		}
	}
}

std::string Level::getSpriteSheet(int gid) {
	if (_spriteSheets.empty()) { return ""; }

	std::map<int, std::string>::iterator it;
	std::string spriteSheet = "";

	for (it = _spriteSheets.begin(); it != _spriteSheets.end(); it++)
	{
		int firstGid = it->first;
		if (firstGid >= gid) {
			break;
		}
		else {
			spriteSheet = it->second;
		}
	}
	return spriteSheet;
}
