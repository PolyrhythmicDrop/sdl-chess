#include "InitGameState.h"

InitGameState::InitGameState() {};

void InitGameState::enter(GameStateMachine* gsm)
{}

void InitGameState::changeState(GameStateMachine* gsm)
{}

void InitGameState::exit(GameStateMachine* gsm)
{}

IGameState& InitGameState::getInstance()
{
	static InitGameState initState;
	return initState;
}

void InitGameState::subscribeToEventManager(EventManager& manager, GameStateMachine* gsm)
{}

void InitGameState::unsubscribeToEventManager(EventManager& manager, GameStateMachine* gsm)
{}
