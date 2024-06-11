#include "TurnBlackGameState.h"
#include "TurnWhiteGameState.h"
#include "EndGameState.h"
#include "easylogging++.h"

TurnBlackGameState::TurnBlackGameState() {};

void TurnBlackGameState::enter(GameStateMachine* gsm)
{
	LOG(TRACE) << "Black Turn Game State entered!";

	// Notify the game manager that the turn has changed
	gsm->getGameManager()->notify("startTurn");

	// Only continue with the turn if the game is not over.
	if (gsm->getGameManager()->getVictoryCondition() == 2)
	{
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
	else
	{
		return;
	}
}

void TurnBlackGameState::changeState(GameStateMachine* gsm, std::string eventString)
{
	if (eventString == "changeTurn")
	{
		gsm->setGameState(gsm->getGameManager(), TurnWhiteGameState::getInstance());
	}
	if (eventString == "endGame")
	{
		gsm->setGameState(gsm->getGameManager(), EndGameState::getInstance());
	}
}

void TurnBlackGameState::exit(GameStateMachine* gsm)
{
	if (gsm->getGameManager()->getCurrentPlayer()->getPlayerType() == Player::HUMAN)
	{
		unsubscribeToEventManager(EventManager::getEventManagerInstance(), gsm);
	}
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