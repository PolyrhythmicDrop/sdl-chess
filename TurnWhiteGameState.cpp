#include "TurnWhiteGameState.h"
#include "GameScene.h"
#include "easylogging++.h"

TurnWhiteGameState::TurnWhiteGameState() {};

void TurnWhiteGameState::enter(GameStateMachine* gsm)
{
	LOG(TRACE) << "White Turn Game State entered!";

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
			detectClickOnObject(x, y, gsm);
		});

}

void TurnWhiteGameState::unsubscribeToEventManager(EventManager& manager, GameStateMachine* gsm)
{
	// TODO: Make sure to unsubscribe from the active boolean when exiting this state.
}

// *** Unique functions ***

void TurnWhiteGameState::detectClickOnObject(int x, int y, GameStateMachine* gsm)
{
	// Set the point to where the mouse was when clicked
	SDL_Point clickPos = { x, y };
	
	// Testing of variables
	LOG(DEBUG) << "getBoardGrid size at 0: " << gsm->getGameScene()->getBoard()->getBoardGrid()->at(0).size();


	// Determine whether the point intersects with any squares.

	// Iterate for every square in the grid:
	
	// For every row, starting at the start of the vector
	for (int row = 0; row < gsm->getGameScene()->getBoard()->getBoardGrid()->size(); ++row)
	{
		for (int column = 0; column < gsm->getGameScene()->getBoard()->getBoardGrid()->at(row).size(); ++column)
		{
			if (SDL_PointInRect(&clickPos, gsm->getGameScene()->getBoard()->getBoardGrid()->at(row).at(column).getDimensions()))
			{
				// Send whether or not the square was clicked to the Debug log
				LOG(DEBUG) << "Square " << gsm->getGameScene()->getBoard()->getBoardGrid()->at(row).at(column).getName() << " clicked!";
			}
		}
	}
	

}