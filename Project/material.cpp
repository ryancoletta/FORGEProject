#include "material.h"
#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "texture.h"

Material::Material(Texture* texture, Shader* shader, Vector2 sourcePosition, Vector2 sourceScale) :
	_texture(texture),
	_shader(shader)
{
	// TODO wrapping behaviour whenever the source position is invalid, kinda weird, maybe refactor
	int w = texture->getWidth();
	int h = texture->getHeight();
	while (sourcePosition.x + sourceScale.x > w || sourcePosition.y + sourceScale.y > h) {
		sourcePosition.x -= w;
		sourcePosition.y += sourceScale.y;
	}

	_sourceRect.x = sourcePosition.x;
	_sourceRect.y = sourcePosition.y;
	_sourceRect.w = sourceScale.x;
	_sourceRect.h = sourceScale.y;
}

Shader* Material::getShader()
{
	return _shader;
}

SDL_Rect Material::getSourceRect()
{
	return _sourceRect;
}

Texture* Material::getTexture()
{
	return _texture;
}

void Material::applyProperties()
{
	_shader->bind();
	_texture->bind(0);
}
