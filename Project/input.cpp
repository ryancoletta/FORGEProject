#include "input.h"
#include "globals.h"

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

bool Input::isKeyHeld(SDL_Scancode key) {
	return _heldKeys[key];
}
bool Input::isKeyDown(SDL_Scancode key) {
	return _downKeys[key];
}
bool Input::isKeyUp(SDL_Scancode key) {
	return _upKeys[key];
}
