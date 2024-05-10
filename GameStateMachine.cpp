#include "GameStateMachine.h"

GameStateMachine::GameStateMachine() :
	_currentState(nullptr),
	_previousState(nullptr),
	_escMenu(nullptr)
{
	assert(!_instantiated);
	_instantiated = true;
	_currentState = &IdleGameState::getInstance();
	_currentState->enter(this);
}

void GameStateMachine::changeState()
{
	_currentState->changeState(this);
}

void GameStateMachine::setGameState(IGameState& newState)
{
	_previousState = _currentState;
	_currentState->exit(this);
	_currentState = &newState;
	_currentState->enter(this);
}

void GameStateMachine::subscribeToEventManager(EventManager& manager)
{
	_currentState->subscribeToEventManager(manager, this);
}

void GameStateMachine::unsubscribeToEventManager(EventManager& manager)
{
	_currentState->unsubscribeToEventManager(manager, this);
}