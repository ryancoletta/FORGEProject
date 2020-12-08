#include "level.h"
#include <stdio.h>
#include <sstream>
#include <algorithm>
#include <cmath>
#include "entitymanager.h"
#include "sprite.h"
#include "graphics.h"
#include "spritemanager.h"
#include "exittile.h"
#include "levelmanager.h"

using namespace tinyxml2;

Level::Level(LevelManager* levelManager, Graphics* graphics, const std::string* levelPath, EntityManager* entityManager, SpriteManager* spriteManager) :
	_entityManager(entityManager),
	_spriteManager(spriteManager)
{
	loadMap(levelManager, graphics, levelPath);
}

Level::~Level() {
	for (int x = 0; x < _tiles.size(); x++) {
		for (int y = 0; y < _tiles[x].size(); y++) {
			delete _tiles[x][y];
		}
	}
}

Tile* Level::getTile(int x, int y) const { return _tiles[x][y]; }

Tile* Level::getTile(Vector2 coordinate) const { return getTile(coordinate.x, coordinate.y); }

bool Level::isCoordinateInRange(int x, int y) const { return (x >= 0) && (y >= 0) && (x < _cols) && (y < _rows); }

bool Level::isCoordinateInRange(Vector2 coordinate) const { return isCoordinateInRange(coordinate.x, coordinate.y); }

void Level::loadMap(LevelManager* levelManager, Graphics* graphics, const std::string* levelPath) {
	XMLDocument doc;
	std::stringstream ss;
	ss << *levelPath;
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

							
							int gid;
							XMLError result = pTile->QueryIntAttribute("gid", &gid);
							

							// handle empty gids
							if (result == XML_NO_ATTRIBUTE) {
								tileCounter++;
								if (pTile->NextSiblingElement("tile")) {
									pTile = pTile->NextSiblingElement("tile");
									continue;
								}
								else { break; }
							}

							SpriteSheet spriteSheet;
							for (int i = 0; i < _spriteSheets.size(); i++) {
								if (_spriteSheets[i].firstGid <= gid) {
									spriteSheet = _spriteSheets[i];
								}
							}

							// handle spritesheets that don't exist
							if (spriteSheet.path == "") {
								//printf("Error: SpriteSheet %s not found", spriteSheet.path);
								tileCounter++;
								if (pTile->NextSiblingElement("tile")) {
									pTile = pTile->NextSiblingElement("tile");
									continue;
								}
								else { break; }
							}

							int spriteSheetGid = gid - spriteSheet.firstGid;

							// get the position of tile in the level
							int x = tileCounter % _cols;
							int y = tileCounter / _cols;
							int posX = x * tileWidth * globals::SPRITE_SCALE;
							int posY = y * tileHeight * globals::SPRITE_SCALE;
							Vector2 finalTilePosition = Vector2(posX, posY);

							// calculate the position of the tile in the tileset
							int spriteSheetWidth = spriteSheet.width;
							int spriteSheetX = spriteSheetGid % (spriteSheetWidth / tileWidth);
							spriteSheetX *= tileWidth;
							int spriteSheetY = spriteSheetGid / (spriteSheetWidth / tileWidth);
							spriteSheetY *= tileHeight;
							Vector2 finalTilesetPosition = Vector2(spriteSheetX, spriteSheetY);

							Sprite* tileSprite = _spriteManager->loadSprite(gid, spriteSheet.path, finalTilesetPosition, tileSize);
							
							if (std::string(layerName) == "BG") {
								if (gid <= static_cast<TileType>(TILE_WALL)) {
									_tiles[x][y] = DBG_NEW Tile(TILE_WALL, tileSprite, Vector2(x, y), finalTilePosition, true);
								}
								else if (gid <= static_cast<TileType>(TILE_OPEN)) {
									_tiles[x][y] = DBG_NEW Tile(TILE_OPEN, tileSprite, Vector2(x, y), finalTilePosition);
								}
								else if (gid <= static_cast<TileType>(TILE_GOAL)) {
									_tiles[x][y] = DBG_NEW ExitTile(levelManager, tileSprite, Vector2(x, y), finalTilePosition);
								}
							}
							else {
								_entityManager->addEntity(static_cast<EntityType>(gid), this, tileSprite, _tiles[x][y]);
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
	doc.Clear();
}

void Level::loadSpriteSheets(Graphics* graphics, XMLElement* mapNode) {
	XMLElement* pSpriteSheet = mapNode->FirstChildElement("tileset");
	if (pSpriteSheet) {
		while (pSpriteSheet) {

			int firstGid;
			pSpriteSheet->QueryAttribute("firstgid", &firstGid);

			const char* source = pSpriteSheet->FirstChildElement("image")->Attribute("source");
			int width = pSpriteSheet->FirstChildElement("image")->IntAttribute("width");

			std::stringstream ss;
			ss << "Assets/" << source;
			SpriteSheet spriteSheet = SpriteSheet(firstGid, width, ss.str());
			_spriteSheets.push_back(spriteSheet);

			pSpriteSheet = pSpriteSheet->NextSiblingElement("tileset");
		}
	}
}

void Level::draw() {
	for (int x = 0; x < _tiles.size(); x++) {
		for (int y = 0; y < _tiles[x].size(); y++) {
			if (_tiles[x][y]) { _tiles[x][y]->draw(); }
		}
	}
}