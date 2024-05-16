#include "ProgramStateMachine.h"

ProgramStateMachine::ProgramStateMachine() :
	_currentState(nullptr),
	_previousState(nullptr),
	_escMenu(nullptr)
{
	assert(!_instantiated);
	_instantiated = true;
	_currentState = &IdleProgramState::getInstance();
	_currentState->enter(this);
}

void ProgramStateMachine::changeState()
{
	_currentState->changeState(this);
}

void ProgramStateMachine::setProgramState(IProgramState& newState)
{
	_previousState = _currentState;
	_currentState->exit(this);
	_currentState = &newState;
	_currentState->enter(this);
}

void ProgramStateMachine::subscribeToEventManager(EventManager& manager)
{
	_currentState->subscribeToEventManager(manager, this);
}

void ProgramStateMachine::unsubscribeToEventManager(EventManager& manager)
{
	_currentState->unsubscribeToEventManager(manager, this);
}