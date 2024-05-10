#include "IdleGameState.h"

IdleGameState::IdleGameState()
{}

IGameState& IdleGameState::getInstance()
{
	static IdleGameState idleGameState;
	return idleGameState;
}

void IdleGameState::enter(GameStateMachine* gsm)
{}

void IdleGameState::changeState(GameStateMachine* gsm)
{}

void IdleGameState::exit(GameStateMachine* gsm)
{}

void IdleGameState::subscribeToEventManager(EventManager & manager, GameStateMachine* gsm)
{}

void IdleGameState::unsubscribeToEventManager(EventManager& manager, GameStateMachine* gsm)
{}