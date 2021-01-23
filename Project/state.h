#pragma once
class State
{
public:
	virtual void Enter() = 0;
	virtual void Execute(int deltaTimeMs) = 0;
	virtual void Exit() = 0;
};

