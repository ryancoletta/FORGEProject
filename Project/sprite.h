#pragma once
#include "globals.h"
#include <SDL.h>
#include <string>
#include <glm/glm.hpp>

class Graphics;
class Texture;
class Shader;

class Sprite
{
public:
	Sprite(Graphics* graphics, const std::string& texturePath, const std::string& vertPath, const std::string& fragPath, Vector2 sourcePosition, Vector2 sourceScale, glm::vec2 offset = glm::vec2(0));
	virtual ~Sprite() {}

	Shader* getShader();
	Texture* getTexture();
	SDL_Rect getSourceRect();

	virtual void update(int deltaTime) {};
	virtual void draw(Vector2 position, const float clockWiseAngleRotation = 0.0f);

protected:
	glm::vec2 _offset;
	SDL_Rect _sourceRect;
	Graphics* _graphics;
	Texture* _texture;
	Texture* palette;
	Shader* _shader;
};

