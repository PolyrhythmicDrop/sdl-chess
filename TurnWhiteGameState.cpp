#include "TurnWhiteGameState.h"
#include "TurnBlackGameState.h"
#include "easylogging++.h"

TurnWhiteGameState::TurnWhiteGameState() {};

void TurnWhiteGameState::enter(GameStateMachine* gsm)
{
	LOG(TRACE) << "White Turn Game State entered!";

	// Notify the game manager that the turn has changed
	gsm->getGameManager()->notify("startTurn");

	if (gsm->getGameManager()->getCurrentPlayer()->getPlayerType() == Player::HUMAN)
	{
		subscribeToEventManager(EventManager::getEventManagerInstance(), gsm);
	}
	else
	{
		// Perform an AI turn
		gsm->getGameManager()->onStockfishTurn();
	}
}

void TurnWhiteGameState::changeState(GameStateMachine* gsm, std::string eventString)
{
	if (eventString == "changeTurn")
	{
		gsm->setGameState(gsm->getGameManager(), TurnBlackGameState::getInstance());
	}
}

void TurnWhiteGameState::exit(GameStateMachine* gsm)
{
	if (gsm->getGameManager()->getCurrentPlayer()->getPlayerType() == Player::HUMAN)
	{
		unsubscribeToEventManager(EventManager::getEventManagerInstance(), gsm);
	}
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
			gsm->getGameManager()->handleClick();
		});

}

void TurnWhiteGameState::unsubscribeToEventManager(EventManager& manager, GameStateMachine* gsm)
{
	// TODO: Make sure to unsubscribe from the active boolean when exiting this state.
	manager.Unsubscribe(SDL_MOUSEBUTTONUP);
}

