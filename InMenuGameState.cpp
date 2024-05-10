#include "InMenuGameState.h"

InMenuGameState::InMenuGameState() {}

IGameState& InMenuGameState::getInstance()
{
	static InMenuGameState inMenuGameState;
	return inMenuGameState;
}

void InMenuGameState::enter(GameStateMachine* gsm)
{}

void InMenuGameState::changeState(GameStateMachine* gsm)
{}

void InMenuGameState::exit(GameStateMachine* gsm)
{}

void InMenuGameState::subscribeToEventManager(EventManager& manager, GameStateMachine* gsm)
{}

void InMenuGameState::unsubscribeToEventManager(EventManager& manager, GameStateMachine* gsm)
{}