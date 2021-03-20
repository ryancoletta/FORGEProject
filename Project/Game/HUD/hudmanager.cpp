#include "hudmanager.h"
#include "text.h"
#include "font.h"
#include "Graphics/graphics.h"
#include "Sprites/spritemanager.h"
#include "hudimage.h"

HudManager::HudManager(Graphics* graphics, SpriteManager* spriteManager) :
	_spriteManager(spriteManager)
{
	_font = DBG_NEW Font(graphics, "Assets/Sprites/1_font_spritesheet.png", glm::vec2(8, 8)); // TODO hardcoded for now, don't really need more than one font though...
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

Text* HudManager::writeText(std::string text, glm::vec2 position, TextAlignment alignment)
{
	Text* newText = DBG_NEW Text(_font, text, position, alignment);
	_allText.push_back(newText);
	return newText;
}

HudImage* HudManager::spawnImage(std::string spriteName, const std::string& texturePath, const std::string& palettePath, const std::string& vertexPath, const std::string& fragmentPath, glm::vec2 sourcePosition, glm::vec2 sourceScale, glm::vec2 destinationPosition)
{
	Sprite* sprite = _spriteManager->loadSprite(spriteName, texturePath, palettePath, vertexPath, fragmentPath, sourcePosition, sourceScale);
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


