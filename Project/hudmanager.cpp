#include "hudmanager.h"
#include "text.h"
#include "font.h"
#include "graphics.h"

HudManager::HudManager(Graphics* graphics) {
	_font = DBG_NEW Font(graphics, "Assets/font.png", Vector2(8, 8)); // TODO hardcoded for now, don't really need more than one font though...

	//TODO temporary text
	Text* newText = DBG_NEW Text(_font, "HUD", Vector2(globals::WINDOW_WIDTH / 2.0f, globals::WINDOW_HEIGHT / 2.0f), MIDDLE_ALIGNED);
	_allText.push_back(newText);
}
HudManager::~HudManager() {
	for (int i = 0; i < _allText.size(); i++) {
		delete _allText[i];
		_allText[i] = NULL;
	}
	_allText.clear();

	delete _font;
	_font = NULL;
}
void HudManager::draw() {
	for (int i = 0; i < _allText.size(); i++) {
		_allText[i]->draw();
	}
}
