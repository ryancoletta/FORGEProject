#include "level.h"
#include <stdio.h>
#include <sstream>
#include <algorithm>
#include <cmath>
#include "Entities/entitymanager.h"
#include "Graphics/graphics.h"
#include "Sprites/spritemanager.h"
#include "Tiles/exittile.h"
#include "Entities/entity.h"
#include "levelmanager.h"
#include "Sprites/sprite.h"
#include "Tiles/switchtile.h"
#include "Tiles/spiketile.h"
#include "Tiles/holetile.h"

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

Tile* Level::getTile(glm::vec2 coordinate) const { return getTile(coordinate.x, coordinate.y); }

bool Level::isCoordinateInRange(int x, int y) const { return (x >= 0) && (y >= 0) && (x < _levelSize.x) && (y < _levelSize.y); }

bool Level::isCoordinateInRange(glm::vec2 coordinate) const { return isCoordinateInRange(coordinate.x, coordinate.y); }

glm::vec2 Level::getLevelSize() const
{
	return _levelSize;
}

void Level::loadMap(LevelManager* levelManager, Graphics* graphics, const std::string* levelPath) {
	XMLDocument doc;
	std::stringstream ss;
	ss << *levelPath;
	assert(doc.LoadFile(ss.str().c_str()) == XML_SUCCESS);

	XMLElement* mapNode = doc.FirstChildElement("map");
	int width = 0;
	int height = 0;
	mapNode->QueryIntAttribute("width", &width);
	mapNode->QueryIntAttribute("height", &height);

	_levelSize.x = (float)width;
	_levelSize.y = (float)height;

	_tiles.resize(_levelSize.x);
	for (int x = 0; x < glm::round(_levelSize.x); x++) {
		_tiles[x].resize(_levelSize.y);
	}

	int tileWidth, tileHeight;
	mapNode->QueryIntAttribute("tilewidth", &tileWidth);
	mapNode->QueryIntAttribute("tileheight", &tileHeight);
	glm::vec2 tileSize(tileWidth, tileHeight);

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
							int x = tileCounter % (int)glm::round(_levelSize.x);
							int y = tileCounter / (int)glm::round(_levelSize.x);
							int posX = (x + 0.5) * tileWidth * globals::SPRITE_SCALE;
							int posY = (y + 0.5) * tileHeight * globals::SPRITE_SCALE;
							glm::vec2 finalTilePosition = glm::vec2(posX, posY);

							// calculate the position of the tile in the tileset, reading from the top left
							int spriteSheetWidth = spriteSheet.width;
							int spriteSheetX = spriteSheetGid % (spriteSheetWidth / tileWidth);
							spriteSheetX *= tileWidth;
							int spriteSheetY = spriteSheetGid / (spriteSheetWidth / tileWidth);
							spriteSheetY *= tileHeight;
							glm::vec2 finalTilesetPosition = glm::vec2(spriteSheetX, spriteSheet.height - tileHeight - spriteSheetY);

							Sprite* tileSprite = _spriteManager->loadSprite(static_cast<GidElement>(gid), spriteSheet.path, "Shaders/base.vert", "Shaders/base.frag", finalTilesetPosition, tileSize);

							if (std::string(layerName) == "BG") {
								if (gid <= GID_TILE_WALL_END) {
									_tiles[x][y] = DBG_NEW Tile(TILE_WALL, tileSprite, glm::vec2(x, y), finalTilePosition, true);
								}
								else if (gid <= GID_TILE_OPEN_END) {
									_tiles[x][y] = DBG_NEW Tile(TILE_OPEN, tileSprite, glm::vec2(x, y), finalTilePosition);
								}
								else if (gid == GID_TILE_HOLE) {
									_tiles[x][y] = DBG_NEW HoleTile(tileSprite, glm::vec2(x, y), finalTilePosition);
								}
								else if (gid == GID_TILE_SWITCH) {
									_tiles[x][y] = DBG_NEW SwitchTile(tileSprite, glm::vec2(x, y), finalTilePosition);
								}
								else if (gid == GID_TILE_GOAL) {
									_tiles[x][y] = DBG_NEW ExitTile(levelManager, tileSprite, glm::vec2(x, y), finalTilePosition);
								}
								else if (gid == GID_TILE_SPIKE_OFF || gid == GID_TILE_SPIKE_ON) {
									_tiles[x][y] = DBG_NEW SpikeTile(tileSprite, glm::vec2(x, y), finalTilePosition, gid == GID_TILE_SPIKE_ON);
								}
							}
							else {
								_entityManager->addEntity(static_cast<GidElement>(gid), this, tileSprite, _tiles[x][y], rotate(glm::vec2(0,1), rotation));
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

			const char* relativeSource = pSpriteSheet->FirstChildElement("image")->Attribute("source");
			std::string absoluteSource = "Assets" + std::string(relativeSource).erase(0,2);

			int width = pSpriteSheet->FirstChildElement("image")->IntAttribute("width");
			int height = pSpriteSheet->FirstChildElement("image")->IntAttribute("height");

			std::stringstream ss;
			ss << absoluteSource.c_str();
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
