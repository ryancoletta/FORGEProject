#include "sprite.h"
#include "Graphics/graphics.h"
#include "Graphics/texture.h"
#include "Graphics/shader.h"

Sprite::Sprite(Graphics* graphics, const std::string& texturePath, const std::string& palettePath, const std::string& vertPath, const std::string& fragPath, glm::vec2 sourcePosition, glm::vec2 sourceScale, glm::vec2 offset) :
	_graphics(graphics),
	_offset(offset),
	_sortingOrder(0)
{
	_texture = _graphics->loadTexture(texturePath);
	_palette = _graphics->loadTexture(palettePath);
	_shader = _graphics->loadShader(vertPath, fragPath);

	_sourceRect.x = static_cast<int>(sourcePosition.x);
	_sourceRect.y = static_cast<int>(sourcePosition.y);
	_sourceRect.w = static_cast<int>(sourceScale.x);
	_sourceRect.h = static_cast<int>(sourceScale.y);
}

void Sprite::draw(glm::vec2 position, const float clockWiseAngleRotation)
{
	_shader->bind();
	_texture->bind(0);

	SDL_Rect destRect = {
		static_cast<int>(position.x + _offset.x),
		static_cast<int>(position.y + _offset.y),
		static_cast<int>(_sourceRect.w * globals::SPRITE_SCALE),
		static_cast<int>(_sourceRect.h * globals::SPRITE_SCALE)
	};
	_graphics->draw(_texture, _palette, _shader, _sourceRect, destRect, clockWiseAngleRotation);
}

Shader* Sprite::getShader()
{
	return _shader;
}

Texture* Sprite::getTexture()
{
	return _texture;
}

SDL_Rect Sprite::getSourceRect()
{
	return _sourceRect;
}

int Sprite::getSortingOrder() { return _sortingOrder; }

void Sprite::setSortingOrder(int sortingOrder) { _sortingOrder = sortingOrder; }
