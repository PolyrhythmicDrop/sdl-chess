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
			int x, y;
			SDL_GetMouseState(&x, &y);
			SDL_Point mousePos = { x, y };
			SDL_Rect boardDim = gsm->getGameScene()->getBoard()->getBoardDimensions();
			SDL_Rect* boardPnt = &boardDim;
			// If the mouse is within the board dimensions, then determine if it clicked on any pieces.
			if (SDL_PointInRect(&mousePos, boardPnt))
			{
				gsm->getGameScene()->getManager()->detectClickOnObject(x, y);
			}
			else
			{
				gsm->getGameScene()->getManager()->deselectPieces();
				gsm->getGameScene()->getManager()->removeActionHighlight();
			}
		});

}

void TurnWhiteGameState::unsubscribeToEventManager(EventManager& manager, GameStateMachine* gsm)
{
	// TODO: Make sure to unsubscribe from the active boolean when exiting this state.
}

