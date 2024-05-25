#include "PauseGameState.h"

#include "easylogging++.h"

PauseGameState::PauseGameState() {};

void PauseGameState::enter(GameStateMachine* gsm)
{
	LOG(TRACE) << "Pause Game State entered!";
}

void PauseGameState::changeState(GameStateMachine* gsm, std::string eventString)
{}

void PauseGameState::exit(GameStateMachine* gsm)
{
	LOG(TRACE) << "Pause Game State exited!";
}

IGameState& PauseGameState::getInstance()
{
	static PauseGameState pauseState;
	return pauseState;
}

void PauseGameState::subscribeToEventManager(EventManager& manager, GameStateMachine* gsm)
{
	// TODO: Subscribe to the Escape Menu's active boolean using its addListener() function. Refer to InMenuProgramState.cpp for a model.

}

void PauseGameState::unsubscribeToEventManager(EventManager& manager, GameStateMachine* gsm)
{
	// TODO: Make sure to unsubscribe from the active boolean when exiting this state.
}