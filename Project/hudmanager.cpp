#include "hudmanager.h"
#include "text.h"
#include "font.h"
#include "graphics.h"

HudManager::HudManager(Graphics* graphics) {
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
}

Text* HudManager::writeText(std::string text, Vector2 position, TextAlignment alignment)
{
	Text* newText = DBG_NEW Text(_font, text, position, alignment);
	_allText.push_back(newText);
	return newText;
}

void HudManager::clearScreen()
{
	for (int i = 0; i < _allText.size(); i++) {
		delete _allText[i];
		_allText[i] = nullptr;
	}
	_allText.clear();
}


