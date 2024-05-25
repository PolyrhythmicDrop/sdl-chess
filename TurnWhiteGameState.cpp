#include "TurnWhiteGameState.h"
#include "easylogging++.h"

TurnWhiteGameState::TurnWhiteGameState() {};

void TurnWhiteGameState::enter(GameStateMachine* gsm)
{
	LOG(TRACE) << "White Turn Game State entered!";

	// Notify the game manager that the turn has changed
	gsm->getGameScene()->getManager()->notify("turnChange");
	// Subscribe to the event manager
	subscribeToEventManager(EventManager::getEventManagerInstance(), gsm);
}

void TurnWhiteGameState::changeState(GameStateMachine* gsm)
{}

void TurnWhiteGameState::exit(GameStateMachine* gsm)
{
	unsubscribeToEventManager(EventManager::getEventManagerInstance(), gsm);
	LOG(TRACE) << "White Turn Game State exited!";
}

IGameState& TurnWhiteGameState::getInstance()
{
	static TurnWhiteGameState whiteTurnState;
	return whiteTurnState;
}

void TurnWhiteGameState::subscribeToEventManager(EventManager& manager, GameStateMachine* gsm)
{
	// TODO: Subscribe to the Escape Menu's active boolean using its addListener() function. Refer to InMenuProgramState.cpp for a model.

	// Subscribe to MouseUp events
	manager.Subscribe(SDL_MOUSEBUTTONUP, [gsm, this](SDL_Event const& event)
		{
			gsm->getGameScene()->getManager()->handleClick();
		});

}

void TurnWhiteGameState::unsubscribeToEventManager(EventManager& manager, GameStateMachine* gsm)
{
	// TODO: Make sure to unsubscribe from the active boolean when exiting this state.

	manager.Unsubscribe(SDL_MOUSEBUTTONUP);
}

