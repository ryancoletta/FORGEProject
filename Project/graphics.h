#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>

class Graphics {
public:
	Graphics();
	~Graphics();

	// loads an image into the spritesheet map
	SDL_Surface* loadImage(const std::string& filePath);

	// draw an image to destRect
	void blitSurface(SDL_Texture* texture, SDL_Rect* sourceRect, SDL_Rect* destRect);
	
	// renders everything to the screen
	void render();

	// clears the screen
	void clear();

	SDL_Renderer* getRenderer() const;

	void setMaxColor(int r, int g, int b);
private:
	int _r, _g, _b;
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	std::map<std::string, SDL_Surface*> _spriteSheets;
};

