#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

class Graphics {
public:
	Graphics();
	~Graphics();
private:
	const int WINDOW_WIDTH = 640;
	const int WINDOW_HEIGHT = 480;
	SDL_Window* _window;
	SDL_Renderer* _renderer;
};

