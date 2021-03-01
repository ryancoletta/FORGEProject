#include "globals.h"
#include "input.h"

bool Input::anyKeyDown() { return !_downKeys.empty(); }

bool Input::isKeyHeld(SDL_Scancode key) { return _heldKeys.count(key) > 0; }

bool Input::isKeyDown(SDL_Scancode key) { return _downKeys.count(key) > 0; }

bool Input::isKeyUp(SDL_Scancode key) { return _upKeys.count(key) > 0; }

void Input::beginNewFrame() {
	_downKeys.clear();
	_upKeys.clear();
}

void Input::keyDownEvent(const SDL_Event& event) {
	_heldKeys[event.key.keysym.scancode] = true;
	_downKeys[event.key.keysym.scancode] = true;
}

void Input::keyUpEvent(const SDL_Event& event) {
	_heldKeys[event.key.keysym.scancode] = false;
	_upKeys[event.key.keysym.scancode] = true;
}
