#include "font.h"
#include "graphics.h"
#include "sprite.h"
#include <SDL.h>
#include "texture.h"

Font::Font(Graphics* graphics, const std::string& filePath, Vector2 charSize) {
	const int CHAR_START_IDX = 32;
	for (int i = 0; i < 96; i++) {
		char thisChar = static_cast<char>(i + CHAR_START_IDX);
		
		// account for wrapping
		Texture* texture = graphics->loadTexture(filePath);
		int w = texture->getWidth();
		int h = texture->getHeight();
		Vector2 charSourcePos = Vector2((i * charSize.x) % w, h - charSize.y - (i * charSize.x) / w * charSize.y) ;
		Sprite* newCharSprite = DBG_NEW Sprite(graphics, filePath, "test.vert", "test.frag", charSourcePos, charSize);
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