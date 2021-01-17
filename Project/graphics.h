#pragma once
#include "globals.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>

class Shader;

class Texture;
class Renderer;
class Material;

class Graphics {
public:
	Graphics();
	~Graphics();

	Texture* loadTexture(const std::string& filePath);
	Shader* loadShader(const std::string& vertPath, const std::string& fragPath);
	Material* loadMaterial(const std::string& texturePath, const std::string& vertPath, const std::string& fragPath, Vector2 sourcePosition, Vector2 sourceScale);

	void render();
	void clear();
	void draw(Material* material, SDL_Rect sourceRect, SDL_Rect destRect, const float clockwiseRotationAngle);
	bool initGL();
private:
	Renderer* _renderer;
	SDL_Window* _window;
	std::map<std::string, SDL_Surface*> _spriteSheets;
	std::map<std::string, Texture*> _textures;
	std::map<std::string, Shader*> _shaders;
};

