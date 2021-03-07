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
	Sprite(Graphics* graphics, const std::string& texturePath, const std::string& palettePath, const std::string& vertPath, const std::string& fragPath, glm::vec2 sourcePosition, glm::vec2 sourceScale, glm::vec2 offset = glm::vec2(0));
	virtual ~Sprite() {}

	Shader* getShader();
	Texture* getTexture();
	SDL_Rect getSourceRect();
	int getSortingOrder();

	void setSortingOrder(int sortingOrder);

	virtual void update(int deltaTime) {};
	virtual void draw(glm::vec2 position, const float clockWiseAngleRotation = 0.0f);

protected:
	glm::vec2 _offset;
	SDL_Rect _sourceRect;
	Graphics* _graphics;
	Texture* _texture;
	Texture* _palette;
	Shader* _shader;
	int _sortingOrder;
};

