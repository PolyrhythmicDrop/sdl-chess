#include "TurnWhiteGameState.h"
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
	

	// Determine whether the point intersects with any squares.

	for (int row = 0; row < gsm->getGameScene()->getBoard()->getBoardGrid()->size(); ++row)
	{
		for (int column = 0; column < gsm->getGameScene()->getBoard()->getBoardGrid()->at(row).size(); ++column)
		{
			if (SDL_PointInRect(&clickPos, gsm->getGameScene()->getBoard()->getBoardGrid()->at(row).at(column).getDimensions()))
			{
				// Declare variable to simplify code
				auto& square = gsm->getGameScene()->getBoard()->getBoardGrid()->at(row).at(column);
				// Send the clicked square's name to the Debug log
				LOG(DEBUG) << "Square " << square.getName() << " clicked!";
				// Detect the piece on the clicked square. If it's a living white piece, call selectPiece(), if it's a black piece or dead, ignore it.
				if (square.getOccupant() != nullptr
					&& square.getOccupant()->getPieceColor() == 1
					&& square.getOccupant()->isAlive())
				{
					selectPiece(square.getOccupant(), gsm);
				}
			}
		}
	}	

}

void TurnWhiteGameState::selectPiece(Piece* piece, GameStateMachine* gsm)
{
	// If any other piece is selected, deselect it
	for (int i = 0; i < gsm->getGameScene()->getAllPieces()->size(); ++i)
	{
		if (gsm->getGameScene()->getAllPieces()->at(i).getSelected())
		{
			gsm->getGameScene()->getAllPieces()->at(i).setSelected(false);
			LOG(DEBUG) << "Piece " << gsm->getGameScene()->getAllPieces()->at(i).getFenName() << " has been deselected!";
		}
	}

	// If the supplied piece is not already selected, select it. If it's already selected, deselect it.
	if (!piece->getSelected())
	{
		piece->setSelected(true);
	}
	else
	{
		piece->setSelected(false);
	}
	LOG(DEBUG) << "Piece " << piece->getFenName() << " on " << piece->getPosition()->getName() << " selected!";
}