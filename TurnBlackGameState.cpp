#include "TurnBlackGameState.h"
#include "easylogging++.h"

TurnBlackGameState::TurnBlackGameState() {};

void TurnBlackGameState::enter(GameStateMachine* gsm)
{
	LOG(TRACE) << "Black Turn Game State entered!";
}

void TurnBlackGameState::changeState(GameStateMachine* gsm)
{}

void TurnBlackGameState::exit(GameStateMachine* gsm)
{
	LOG(TRACE) << "Black Turn Game State exited!";
}

IGameState& TurnBlackGameState::getInstance()
{
	static TurnBlackGameState blackTurnState;
	return blackTurnState;
}

void TurnBlackGameState::subscribeToEventManager(EventManager& manager, GameStateMachine* gsm)
{
	// TODO: Subscribe to the Escape Menu's active boolean using its addListener() function. Refer to InMenuProgramState.cpp for a model.

}

void TurnBlackGameState::unsubscribeToEventManager(EventManager& manager, GameStateMachine* gsm)
{
	// TODO: Make sure to unsubscribe from the active boolean when exiting this state.
}