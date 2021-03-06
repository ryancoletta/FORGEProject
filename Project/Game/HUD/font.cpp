#include "font.h"
#include "Graphics/graphics.h"
#include "Sprites/sprite.h"
#include <SDL.h>
#include "Graphics/texture.h"

Font::Font(Graphics* graphics, const std::string& filePath, glm::uvec2 charSize) {
	const int CHAR_START_IDX = 32;
	for (int i = 0; i < 96; i++) {
		char thisChar = static_cast<char>(i + CHAR_START_IDX);
		
		// account for wrapping
		Texture* texture = graphics->loadTexture(filePath);
		int w = texture->getWidth();
		int h = texture->getHeight();
		glm::vec2 charSourcePos = glm::uvec2((i * charSize.x) % w, h - charSize.y - (i * charSize.x) / w * charSize.y) ;
		std::string palettePath = "Assets/Palettes/logo_palette.png";
		Sprite* newCharSprite = DBG_NEW Sprite(graphics, filePath, palettePath, "Shaders/base.vert", "Shaders/base.frag", charSourcePos, charSize);
		_fontMap.insert(std::pair<char, Sprite*>(thisChar, newCharSprite));
	}
}

Font::~Font() {
	std::map<char, Sprite*>::iterator it;
	for (it = _fontMap.begin(); it != _fontMap.end(); it++)
	{
		delete it->second;
		it->second = nullptr;
	}
	_fontMap.clear();
}

Sprite* Font::getCharSprite(char c) {
	return _fontMap[c];
}