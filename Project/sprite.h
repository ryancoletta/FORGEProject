#pragma once
#include "globals.h"
#include <SDL.h>
#include <string>

class Graphics;
class Texture;
class Shader;

class Sprite
{
public:
	Sprite(Graphics* graphics, const std::string& texturePath, const std::string& vertPath, const std::string& fragPath, Vector2 sourcePosition, Vector2 sourceScale);
	virtual ~Sprite() {}

	Shader* getShader();
	Texture* getTexture();
	SDL_Rect getSourceRect();

	virtual void update(int deltaTime) {};
	virtual void draw(Vector2 position, const float clockWiseAngleRotation = 0.0f);

protected:
	SDL_Rect _sourceRect;
	Graphics* _graphics;
	Texture* _texture;
	Shader* _shader;
};

