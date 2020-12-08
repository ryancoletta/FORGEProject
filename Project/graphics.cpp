#include "globals.h"
#include "graphics.h"
#include <SDL_ttf.h>
#include "globals.h"

Graphics::Graphics()
{
	SDL_CreateWindowAndRenderer(globals::WINDOW_WIDTH, globals::WINDOW_HEIGHT, 0, &_window, &_renderer);
	SDL_SetRenderDrawColor(_renderer, 0xFF, 0x69, 0xB4, 0xFF); // debug pink
	SDL_SetWindowTitle(_window, "FORGE Project");
}

Graphics::~Graphics() {
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
}

SDL_Renderer* Graphics::getRenderer() const { return _renderer; }

SDL_Surface* Graphics::loadImage(const std::string& filePath) {
	if (_spriteSheets.count(filePath) == 0) {
		_spriteSheets[filePath] = IMG_Load(filePath.c_str());
	}
	return _spriteSheets[filePath];
}

void Graphics::blitSurface(SDL_Texture* texture, SDL_Rect* sourceRect, SDL_Rect* destRect) {
	SDL_RenderCopy(_renderer, texture, sourceRect, destRect);
}

void Graphics::render() { SDL_RenderPresent(_renderer); }

void Graphics::clear() { SDL_RenderClear(_renderer); }