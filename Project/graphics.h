#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>

class Shader;

class Graphics {
public:
	Graphics();
	~Graphics();

	SDL_Renderer* getRenderer() const;

	SDL_Surface* loadImage(const std::string& filePath);
	void blitSurface(SDL_Texture* texture, SDL_Rect* sourceRect, SDL_Rect* destRect, const int clockWiseAngleRotation = 0);
	void render();
	void clear();

	bool initGL();

private:
	Shader* _shader;

	SDL_Window* _window;
	SDL_Renderer* _renderer;
	std::map<std::string, SDL_Surface*> _spriteSheets;
};

