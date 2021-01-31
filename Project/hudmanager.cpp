#include "hudmanager.h"
#include "text.h"
#include "font.h"
#include "graphics.h"
#include "spritemanager.h"
#include "hudimage.h"

HudManager::HudManager(Graphics* graphics, SpriteManager* spriteManager) :
	_spriteManager(spriteManager)
{
	_font = DBG_NEW Font(graphics, "Assets/font.png", Vector2(8, 8)); // TODO hardcoded for now, don't really need more than one font though...
}

HudManager::~HudManager() {
	clearScreen();

	delete _font;
	_font = nullptr;
}

void HudManager::draw() {
	for (int i = 0; i < _allText.size(); i++) {
		_allText[i]->draw();
	}
	for (int i = 0; i < _allImages.size(); i++) {
		_allImages[i]->draw();
	}
}

Text* HudManager::writeText(std::string text, Vector2 position, TextAlignment alignment)
{
	Text* newText = DBG_NEW Text(_font, text, position, alignment);
	_allText.push_back(newText);
	return newText;
}

HudImage* HudManager::spawnImage(std::string spriteName, const std::string& texturePath, const std::string& vertexPath, const std::string& fragmentPath, Vector2 sourcePosition, Vector2 sourceScale, Vector2 destinationPosition)
{
	Sprite* sprite = _spriteManager->loadSprite(spriteName, texturePath, vertexPath, fragmentPath, sourcePosition, sourceScale);
	HudImage* newImage = DBG_NEW HudImage(sprite, destinationPosition);
	_allImages.push_back(newImage);
	return newImage;
}

void HudManager::clearScreen()
{
	for (int i = 0; i < _allText.size(); i++) {
		delete _allText[i];
		_allText[i] = nullptr;
	}
	for (int i = 0; i < _allImages.size(); i++) {
		delete _allImages[i];
		_allImages[i] = nullptr;
	}
	_allText.clear();
	_allImages.clear();
}


