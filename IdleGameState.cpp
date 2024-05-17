#include "IdleGameState.h"
#include "easylogging++.h"

IdleGameState::IdleGameState() {};

void IdleGameState::enter(GameStateMachine* gsm)
{
	LOG(TRACE) << "Idle Game State entered!";
}

void IdleGameState::changeState(GameStateMachine* gsm)
{}

void IdleGameState::exit(GameStateMachine* gsm)
{
	LOG(TRACE) << "Idle Game State exited!";
}

IGameState& IdleGameState::getInstance()
{
	static IdleGameState idleState;
	return idleState;
}

void IdleGameState::subscribeToEventManager(EventManager& manager, GameStateMachine* gsm)
{}

void IdleGameState::unsubscribeToEventManager(EventManager& manager, GameStateMachine* gsm)
{}