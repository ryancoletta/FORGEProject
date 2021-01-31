#pragma once

class State;

// TODO gamestate manager seperate
class StateMachine
{
public:
	void ChangeState(State* newState);
	void ExecuteStateUpdate(int deltaTimeMs);
private:
	State* _currentState;
};

