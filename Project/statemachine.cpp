#include "statemachine.h"
#include "state.h"

void StateMachine::ChangeState(State* newState)
{
	if (_currentState != nullptr) {
		_currentState->Exit();
	}
	_currentState = newState;
	_currentState->Enter();
}

void StateMachine::ExecuteStateUpdate(int deltaTimeMs)
{
	if (_currentState != nullptr) {
		_currentState->Execute(deltaTimeMs);
	}
}
