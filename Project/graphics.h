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

	SDL_Renderer* getRenderer() const;

	SDL_Surface* loadImage(const std::string& filePath);
	Texture* loadTexture(const std::string& filePath);
	Shader* loadShader(const std::string& vertPath, const std::string& fragPath);
	Material* loadMaterial(const std::string& texturePath, const std::string& vertPath, const std::string& fragPath, Vector2 sourcePosition, Vector2 sourceScale);

	void blitSurface(SDL_Texture* texture, SDL_Rect* sourceRect, SDL_Rect* destRect, const int clockWiseAngleRotation = 0);
	void render();
	void clear();
	void draw(Material* material, SDL_Rect destRect, const float clockwiseRotationAngle);
	bool initGL();
private:
	Renderer* _rendererer;
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	std::map<std::string, SDL_Surface*> _spriteSheets;
	std::map<std::string, Texture*> _textures;
	std::map<std::string, Shader*> _shaders;
};

