#include "sprite.h"
#include "graphics.h"
#include "texture.h"
#include "shader.h"

Sprite::Sprite(Graphics* graphics, const std::string& texturePath, const std::string& vertPath, const std::string& fragPath, Vector2 sourcePosition, Vector2 sourceScale) :
	_graphics(graphics)
{
	_texture = _graphics->loadTexture(texturePath);
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
		position.x,
		position.y,
		_sourceRect.w * globals::SPRITE_SCALE,
		_sourceRect.h * globals::SPRITE_SCALE
	};
	_graphics->draw(_texture, _shader, _sourceRect, destRect, clockWiseAngleRotation);
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
