#pragma once
#include "graphics.h"
#include "entityManager.h"
#include "state.h"
#include "statemachine.h"

class Graphics;
class EntityManager;
class AnimationManager;
class SpriteManager;
class LevelManager;
class Input;
class HudManager;
class StateMachine;

class Game {
public:
	Game();
	~Game();
	void play();

private:
	class BaseState : public State
	{
	public:
		BaseState(Game* owner) : _owner(owner) {};

		virtual void Enter() override {};
		virtual void Execute(int deltaTimeMs) override;
		virtual void Exit() override {};
	protected:
		Game* _owner;
		SDL_Event _event;
	};

	class TitleState : public BaseState
	{
	public:
		TitleState(Game* owner) : BaseState(owner) {};

		void Enter() override;
		void Execute(int deltaTimeMs) override;
		void Exit() override;
	private:
		int _timer;
	};

	class LevelState : public BaseState
	{
	public:
		LevelState(Game* owner) : BaseState(owner) {};

		void Enter() override;
		void Execute(int deltaTimeMs) override;
		void Exit() override;
	private:
		int _turn;
		Entity* _playerEntity;
	};

	void draw();
	void update(int deltaTime);

	bool _gameOver;
	Uint32 _nextLevelEvent;
	LevelManager* _levelManager;
	EntityManager* _entityManager;
	Graphics* _graphics;
	AnimationManager* _animationManager;
	SpriteManager* _spriteManager;
	Input* _input;
	HudManager* _hudManager;
	Sprite* _background;
	StateMachine* _stateMachine;

	TitleState* _titleState;
	LevelState* _levelState;
};

