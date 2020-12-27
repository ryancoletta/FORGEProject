#include "font.h"
#include "sprite.h"

Font::Font(Graphics* graphics, const std::string& filePath, Vector2 charSize) {
	const int CHAR_START_IDX = 32;
	for (int i = 0; i < 96; i++) {
		char thisChar = static_cast<char>(i + CHAR_START_IDX);
		Sprite* newCharSprite = DBG_NEW Sprite(graphics, filePath, Vector2(i * charSize.x, 0), charSize);
		_fontMap.insert(std::pair<char, Sprite*>(thisChar, newCharSprite));
	}
}

Font::~Font() {
	std::map<char, Sprite*>::iterator it;
	for (it = _fontMap.begin(); it != _fontMap.end(); it++)
	{
		delete it->second;
		it->second = NULL;
	}
	_fontMap.clear();
}

Sprite* Font::getCharSprite(char c) {
	return _fontMap[c];
}