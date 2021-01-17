#pragma once
#include "globals.h"
#include <SDL.h>

class Graphics;
class Texture;
class Shader;

class Material
{
public:
	Material(Texture* texture, Shader* shader, Vector2 sourcePosition, Vector2 sourceScale);

	Shader* getShader();
	SDL_Rect getSourceRect();
	Texture* getTexture();

	void applyProperties();

private:
	SDL_Rect _sourceRect;
	Texture* _texture;
	Shader* _shader;
};

