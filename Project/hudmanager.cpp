#include "hudmanager.h"
#include "text.h"
#include "font.h"
#include "graphics.h"

HudManager::HudManager(Graphics* graphics) {
	_font = DBG_NEW Font(graphics, "Assets/font.png", Vector2(8, 8)); // TODO hardcoded for now, don't really need more than one font though...

	//TODO temporary text
	Text* newText = DBG_NEW Text(_font, "Very text.", Vector2(globals::WINDOW_WIDTH / 2.0, globals::WINDOW_HEIGHT / 6.0), MIDDLE_ALIGNED);
	_allText.push_back(newText);

	newText = DBG_NEW Text(_font, "Much type.", Vector2(globals::WINDOW_WIDTH, globals::WINDOW_HEIGHT / 2.0), RIGHT_ALIGNED);
	_allText.push_back(newText);

	newText = DBG_NEW Text(_font, "Wow!", Vector2(20, globals::WINDOW_HEIGHT - globals::WINDOW_HEIGHT / 7.0));
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
