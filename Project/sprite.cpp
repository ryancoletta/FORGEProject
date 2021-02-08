#include "sprite.h"
#include "graphics.h"
#include "texture.h"
#include "shader.h"

Sprite::Sprite(Graphics* graphics, const std::string& texturePath, const std::string& palettePath, const std::string& vertPath, const std::string& fragPath, Vector2 sourcePosition, Vector2 sourceScale, glm::vec2 offset) :
	_graphics(graphics),
	_offset(offset),
	_sortingOrder(0)
{
	_texture = _graphics->loadTexture(texturePath);
	_palette = _graphics->loadTexture(palettePath);
	_shader = _graphics->loadShader(vertPath, fragPath);

	_sourceRect.x = sourcePosition.x;
	_sourceRect.y = sourcePosition.y;
	_sourceRect.w = sourceScale.x;
	_sourceRect.h = sourceScale.y;
}

void Sprite::draw(Vector2 position, const float clockWiseAngleRotation)
{
	_shader->bind();
	_texture->bind(0);

	SDL_Rect destRect = {
		position.x + _offset.x,
		position.y + _offset.y,
		_sourceRect.w * globals::SPRITE_SCALE,
		_sourceRect.h * globals::SPRITE_SCALE
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
