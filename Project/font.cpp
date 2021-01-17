#include "font.h"
#include "sprite.h"
#include "graphics.h"
#include "spriteinstance.h"
#include "material.h"
#include <SDL.h>

Font::Font(Graphics* graphics, const std::string& filePath, Vector2 charSize) {
	const int CHAR_START_IDX = 32;
	for (int i = 0; i < 96; i++) {
		char thisChar = static_cast<char>(i + CHAR_START_IDX);

		Material* material = graphics->loadMaterial(filePath, "test.vert", "test.frag", Vector2(i * charSize.x, 0), charSize);
		SpriteInstance* newCharSprite = DBG_NEW SpriteInstance(graphics, material);
		_fontMap.insert(std::pair<char, SpriteInstance*>(thisChar, newCharSprite));
	}
}

Font::~Font() {
	std::map<char, SpriteInstance*>::iterator it;
	for (it = _fontMap.begin(); it != _fontMap.end(); it++)
	{
		delete it->second;
		it->second = NULL;
	}
	_fontMap.clear();
}

SpriteInstance* Font::getCharSprite(char c) {
	return _fontMap[c];
}