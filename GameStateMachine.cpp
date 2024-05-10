#include "GameStateMachine.h"

GameStateMachine::GameStateMachine() :
	_currentState(nullptr),
	_previousState(nullptr)
{
	assert(!_instantiated);
	_instantiated = true;
	_currentState = &IdleGameState::getInstance();
	_currentState->enter(this);
}

void GameStateMachine::changeState()
{}

void GameStateMachine::setGameState(IGameState& newState)
{}

void GameStateMachine::subscribeToEventManager(EventManager& manager)
{}

void GameStateMachine::unsubscribeToEventManager(EventManager& manager)
{}