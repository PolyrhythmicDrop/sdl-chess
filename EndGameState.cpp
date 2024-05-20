#include "EndGameState.h"
#include "easylogging++.h"

EndGameState::EndGameState() {};

void EndGameState::enter(GameStateMachine* gsm)
{
	LOG(TRACE) << "End Game State entered!";
}

void EndGameState::changeState(GameStateMachine* gsm)
{}

void EndGameState::exit(GameStateMachine* gsm)
{
	LOG(TRACE) << "End Game State exited!";
}

IGameState& EndGameState::getInstance()
{
	static EndGameState endGameState;
	return endGameState;
}

void EndGameState::subscribeToEventManager(EventManager& manager, GameStateMachine* gsm)
{
	// TODO: Subscribe to the Escape Menu's active boolean using its addListener() function. Refer to InMenuProgramState.cpp for a model.

}

void EndGameState::unsubscribeToEventManager(EventManager& manager, GameStateMachine* gsm)
{
	// TODO: Make sure to unsubscribe from the active boolean when exiting this state.
}