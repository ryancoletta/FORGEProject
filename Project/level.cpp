#include "level.h"
#include <stdio.h>
#include <sstream>
#include <algorithm>
#include <cmath>
#include "entitymanager.h"
#include "graphics.h"
#include "spritemanager.h"
#include "exittile.h"
#include "entity.h"
#include "levelmanager.h"
#include "sprite.h"
#include "switchtile.h"
#include "spiketile.h"
#include "crackedtile.h"

using namespace tinyxml2;

Level::Level(LevelManager* levelManager, Graphics* graphics, const std::string* levelPath, EntityManager* entityManager, SpriteManager* spriteManager) :
	_entityManager(entityManager),
	_spriteManager(spriteManager)
{
	loadMap(levelManager, graphics, levelPath);
	connectTiles();
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

bool Level::isCoordinateInRange(int x, int y) const { return (x >= 0) && (y >= 0) && (x < _levelSize.x) && (y < _levelSize.y); }

bool Level::isCoordinateInRange(Vector2 coordinate) const { return isCoordinateInRange(coordinate.x, coordinate.y); }

Vector2 Level::getLevelSize() const
{
	return _levelSize;
}

void Level::loadMap(LevelManager* levelManager, Graphics* graphics, const std::string* levelPath) {
	XMLDocument doc;
	std::stringstream ss;
	ss << *levelPath;
	doc.LoadFile(ss.str().c_str());

	XMLElement* mapNode = doc.FirstChildElement("map");
	mapNode->QueryIntAttribute("width", &_levelSize.x);
	mapNode->QueryIntAttribute("height", &_levelSize.y);

	_tiles.resize(_levelSize.x);
	for (int x = 0; x < _levelSize.x; x++) {
		_tiles[x].resize(_levelSize.y);
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
							unsigned gid;
							XMLError result = pTile->QueryUnsignedAttribute("gid", &gid);

							int rotation = getGidRotation(gid);

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
							int x = tileCounter % _levelSize.x;
							int y = tileCounter / _levelSize.x;
							int posX = x * tileWidth * globals::SPRITE_SCALE;
							int posY = y * tileHeight * globals::SPRITE_SCALE;
							Vector2 finalTilePosition = Vector2(posX, posY);

							// calculate the position of the tile in the tileset, reading from the top left
							int spriteSheetWidth = spriteSheet.width;
							int spriteSheetX = spriteSheetGid % (spriteSheetWidth / tileWidth);
							spriteSheetX *= tileWidth;
							int spriteSheetY = spriteSheetGid / (spriteSheetWidth / tileWidth);
							spriteSheetY *= tileHeight;
							Vector2 finalTilesetPosition = Vector2(spriteSheetX, spriteSheet.height - tileHeight - spriteSheetY);

							Sprite* tileSprite = _spriteManager->loadSprite(static_cast<GidElement>(gid), spriteSheet.path, "base.vert", "base.frag", finalTilesetPosition, tileSize);

							if (std::string(layerName) == "BG") {
								if (gid <= GID_TILE_WALL_END) {
									_tiles[x][y] = DBG_NEW Tile(TILE_WALL, tileSprite, Vector2(x, y), finalTilePosition, true);
								}
								else if (gid <= GID_TILE_OPEN_END) {
									_tiles[x][y] = DBG_NEW Tile(TILE_OPEN, tileSprite, Vector2(x, y), finalTilePosition);
								}
								else if (gid == GID_TILE_CRACK_1 || gid == GID_TILE_CRACK_2 || gid == GID_TILE_CRACK_3) {
									_tiles[x][y] = DBG_NEW CrackedTile(gid - GID_TILE_CRACK_1, tileSprite, Vector2(x, y), finalTilePosition);
								}
								else if (gid == GID_TILE_SWITCH) {
									_tiles[x][y] = DBG_NEW SwitchTile(tileSprite, Vector2(x, y), finalTilePosition);
								}
								else if (gid == GID_TILE_GOAL) {
									_tiles[x][y] = DBG_NEW ExitTile(levelManager, tileSprite, Vector2(x, y), finalTilePosition);
								}
								else if (gid == GID_TILE_SPIKE_OFF || gid == GID_TILE_SPIKE_ON) {
									_tiles[x][y] = DBG_NEW SpikeTile(tileSprite, Vector2(x, y), finalTilePosition, gid == GID_TILE_SPIKE_ON);
								}
							}
							else {
								_entityManager->addEntity(static_cast<GidElement>(gid), this, tileSprite, _tiles[x][y], Vector2::rotate(Vector2::up(), rotation));
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
int Level::getGidRotation(unsigned &gid) {
	const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
	const unsigned FLIPPED_VERTICALLY_FLAG = 0x40000000;
	const unsigned FLIPPED_DIAGONALLY_FLAG = 0x20000000;

	bool flippedHorizontally = (gid & FLIPPED_HORIZONTALLY_FLAG);
	bool flippedVertically = (gid & FLIPPED_VERTICALLY_FLAG);
	bool flippedDiagonally = (gid & FLIPPED_DIAGONALLY_FLAG);
	bool clockWise90 = flippedHorizontally && flippedDiagonally;
	bool clockWise180 = flippedHorizontally && flippedVertically;
	bool clockWise270 = flippedDiagonally && flippedVertically;

	gid &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);

	if (clockWise90) {
		return 90;
	}
	else if (clockWise180) {
		return 180;
	}
	else if (clockWise270) {
		return 270;
	}
	else return 0;
}

void Level::connectTiles()
{
	for (int y = 0; y < _tiles.size(); y++) {
		for (int x = 0; x < _tiles[y].size(); x++) {
			Tile* tile = _tiles[x][y];
			if (tile && tile->getTileType() == TILE_SWITCH) {
				static_cast<SwitchTile*>(tile)->findAllSpikeTiles(this);
			}
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
			int width = pSpriteSheet->FirstChildElement("image")->IntAttribute("width");
			int height = pSpriteSheet->FirstChildElement("image")->IntAttribute("height");

			std::stringstream ss;
			ss << "Assets/" << source;
			SpriteSheet spriteSheet = SpriteSheet(firstGid, width, height, ss.str());
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

void Level::update(int deltaTimeMs)
{
	for (int x = 0; x < _tiles.size(); x++) {
		for (int y = 0; y < _tiles[x].size(); y++) {
			if (_tiles[x][y]) { _tiles[x][y]->update(deltaTimeMs); }
		}
	}
}

void Level::undo(int turn)
{
	for (int x = 0; x < _tiles.size(); x++) {
		for (int y = 0; y < _tiles[x].size(); y++) {
			if (_tiles[x][y]) { _tiles[x][y]->undo(turn); }
		}
	}
}

void Level::reset()
{
	for (int x = 0; x < _tiles.size(); x++) {
		for (int y = 0; y < _tiles[x].size(); y++) {
			if (_tiles[x][y]) { _tiles[x][y]->reset(); }
		}
	}
}
