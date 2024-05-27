#include "TurnBlackGameState.h"
#include "TurnWhiteGameState.h"
#include "easylogging++.h"

TurnBlackGameState::TurnBlackGameState() {};

void TurnBlackGameState::enter(GameStateMachine* gsm)
{
	LOG(TRACE) << "Black Turn Game State entered!";

	// Notify the game manager that the turn has changed
	gsm->getGameManager()->notify("turnChange");

	// Set any active en passant flags for this color to false so that any en passant captures
	// must occur directly after pawn's first move
	gsm->getGameManager()->endPassant();

	// Subscribe to the event manager
	subscribeToEventManager(EventManager::getEventManagerInstance(), gsm);
}

void TurnBlackGameState::changeState(GameStateMachine* gsm, std::string eventString)
{
	if (eventString == "changeTurn")
	{
		gsm->setGameState(gsm->getGameManager(), TurnWhiteGameState::getInstance());
	}
}

void TurnBlackGameState::exit(GameStateMachine* gsm)
{
	LOG(TRACE) << "Black Turn Game State exited!";
	unsubscribeToEventManager(EventManager::getEventManagerInstance(), gsm);
}

IGameState& TurnBlackGameState::getInstance()
{
	static TurnBlackGameState blackTurnState;
	return blackTurnState;
}

void TurnBlackGameState::subscribeToEventManager(EventManager& manager, GameStateMachine* gsm)
{
	// TODO: Subscribe to the Escape Menu's active boolean using its addListener() function. Refer to InMenuProgramState.cpp for a model.
	// 
	// Subscribe to MouseUp events
	manager.Subscribe(SDL_MOUSEBUTTONUP, [gsm, this](SDL_Event const& event)
		{
			gsm->getGameManager()->handleClick();
		});

}

void TurnBlackGameState::unsubscribeToEventManager(EventManager& manager, GameStateMachine* gsm)
{
	// TODO: Make sure to unsubscribe from the active boolean when exiting this state.
	
	manager.Unsubscribe(SDL_MOUSEBUTTONUP);

}