#pragma once

class State;

class StateMachine
{
public:
	void ChangeState(State* newState);
	void ExecuteStateUpdate(int deltaTimeMs);
private:
	State* _currentState;
};

