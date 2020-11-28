#pragma once
#include <map>
#include <SDL.h>

class Input {
public:
	void beginNewFrame();
	void keyDownEvent(const SDL_Event& event);
	void keyUpEvent(const SDL_Event &event);
	bool isKeyHeld(SDL_Scancode key);
	bool isKeyDown(SDL_Scancode key);
	bool isKeyUp(SDL_Scancode key);
private:
	std::map<SDL_Scancode, bool> _heldKeys;
	std::map<SDL_Scancode, bool> _downKeys;
	std::map<SDL_Scancode, bool> _upKeys;
};

