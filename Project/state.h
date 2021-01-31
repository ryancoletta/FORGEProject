#pragma once
class State
{
public:
	virtual void Enter() = 0;
	virtual void Execute(int deltaTimeMs) = 0;
	virtual void Exit() = 0;
};

// TODO void Enter(int i)
// TODO have to specialize states at some point

