#pragma once
#include "Graphics/graphics.h"
#include "Entities/entityManager.h"
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
class Text;
class PlayerEntity;
class SoundManager;

class Game {
public:
	Game();
	~Game();
	void play();

private:
	// TODO move states into their own files
	class BaseState : public State
	{
	public:
		BaseState(Game* owner);

		virtual void Enter() override;
		virtual void Execute(int deltaTimeMs) override;
		virtual void Exit() override {};
	protected:
		Game* _owner;
		SDL_Event _event;
		bool _stateComplete;
		float _stateEnterTimeMS;
		float _fade;
	};

	class TitleState : public BaseState
	{
	public:
		TitleState(Game* owner);

		void Enter() override;
		void Execute(int deltaTimeMs) override;
		void Exit() override;
	private:
		Text* _startText;
		Text* _creditText;
	};

	class LevelState : public BaseState
	{
	public:
		LevelState(Game* owner);

		void Enter() override;
		void Execute(int deltaTimeMs) override;
		void Exit() override;
	private:
		int _turn;
		PlayerEntity* _playerEntity;
		Text* _helpText;
		float _lastInputTimeMS;
	};

	void draw();
	void update(int deltaTime);

	// TODO make these singletons
	// TODO make a singletonstructure that holds these
	// TODO make game a global object
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

