#pragma once
#include "graphics.h"
#include "entityManager.h"

class Graphics;
class EntityManager;
class AnimationManager;
class SpriteManager;
class LevelManager;
class Input;
class Text; // TODO remove

class Game {
public:
	Game();
	~Game();
	void play();

private:
	void draw();
	void update(int deltaTime);

	int _turn;
	SDL_Event _event;
	Uint32 _nextLevelEvent;
	LevelManager* _levelManager;
	EntityManager* _entityManager;
	Graphics* _graphics;
	AnimationManager* _animationManager;
	SpriteManager* _spriteManager;
	Input* _input;

	// TODO temp, remove
	Text* _text;
};

