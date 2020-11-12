#include "graphics.h"

Graphics::Graphics() {
	SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &_window, &_renderer);
	SDL_SetWindowTitle(_window, "FORGE Project");
}

Graphics::~Graphics() {
	SDL_DestroyWindow(_window);
}