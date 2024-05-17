#include "IdleGameState.h"

IdleGameState::IdleGameState() {};

void IdleGameState::enter(GameStateMachine* gsm)
{}

void IdleGameState::changeState(GameStateMachine* gsm)
{}

void IdleGameState::exit(GameStateMachine* gsm)
{}

IGameState& IdleGameState::getInstance()
{
	static IdleGameState idleState;
	return idleState;
}

void IdleGameState::subscribeToEventManager(EventManager& manager, GameStateMachine* gsm)
{}

void IdleGameState::unsubscribeToEventManager(EventManager& manager, GameStateMachine* gsm)
{}