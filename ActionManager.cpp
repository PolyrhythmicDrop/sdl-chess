#include "ActionManager.h"
#include "GameScene.h"
#include <conio.h>
#include "easylogging++.h"

void ActionManager::movePiece(Piece* piece, Square* target)
{
	std::pair<int, int> moveDistance = { 0, 0 };

	// Move distance is the piece's board index subtracted from the target's move index.
	moveDistance = { target->getBoardIndex().first - piece->getSquare()->getBoardIndex().first,
					target->getBoardIndex().second - piece->getSquare()->getBoardIndex().second };

	if (!target->getOccupied())
	{
		// Unoccupy the square the piece is currently on
		piece->getSquare()->setOccupied(false);

		// Move the piece to the target position and occupy the square.
		piece->setSquare(target);
	}

	// Pawn-specific movement and rules
	// *********************************

	// If this was the piece's first move, set first move to false for future moves.
	if (piece->getFirstMove())
	{
		piece->setFirstMove(false);
		// Set whether or not the piece can be captured en passant.
		if (piece->getPieceType() == Piece::PAWN && abs(moveDistance.first) == 2)
		{
			piece->setPassantable(true);
		}
	}
	else
	{
		if (piece->getPassantable() == true)
		{
			piece->setPassantable(false);
		}
	}

	// Notify the GameManager that the position has changed.
	_gm->notify(piece, "pieceMove");
}

void ActionManager::capturePiece(Piece* attacker, Piece* defender)
{
	Square* defPos = defender->getSquare();
	// De-occupy the defender's square
	defPos->setOccupied(false);
	// Unalive the defender
	defender->setAlive(false);
	// Set the defender's position to null
	defender->setSquare(nullptr);
	// Add the defender to the captured piece location
	_gm->_gameScene->addToCapturedPieces(defender);
	// Move the attacking piece into the defender's position
	movePiece(attacker, defPos);
}

void ActionManager::promotePawn(Piece* piece)
{
	// TODO: Handle in the console for now, later I'll make a GUI for it
	bool promote = false;
	bool run = true;
	char input = NULL;

	// Render map vectors for updating the texture if necessary
	std::vector<std::pair<GameObject*, SDL_Texture*>> vect;
	std::pair<GameObject*, SDL_Texture*> pair;
	pair.first = piece;
	pair.second = piece->getGraphics()->getSdlTexture();
	vect.push_back(pair);

	while (run = true)
	{
		system("cls");
		try
		{
			std::cout << "Do you want to promote the pawn on " << piece->getSquare()->getName() << "?\nY/n\n";
			input = _getch();
			if (input != 'Y' && input != 'y' && input != 'n' && input != 'N')
			{
				throw input;
			}
			else if (input == 'Y' || input == 'y')
			{
				ServiceLocator::getGraphics().removeFromRenderMap(vect);
				try
				{
				// Select piece to turn into
				std::cout << "Select which figure to promote to:\n1. Queen\n2. Rook\n3. Bishop\n4. Knight\n";
				char choice = _getch();
				
					switch (choice)
					{
					case '1':
						piece->changeType(Piece::Figure::QUEEN);
						run = false;
						break;
					case '2':
						piece->changeType(Piece::Figure::ROOK);
						run = false;
						break;
					case '3':
						piece->changeType(Piece::Figure::BISHOP);
						run = false;
						break;
					case '4':
						piece->changeType(Piece::Figure::KNIGHT);
						run = false;
						break;
					default:
						throw choice;
						continue;
					}
				}
				catch (char e)
				{
					LOG(ERROR) << "Invalid input: " << e;
					ServiceLocator::getGraphics().addToRenderMap(2, vect);
					continue;
				}
				vect.clear();
				pair.first = piece;
				pair.second = piece->getGraphics()->getSdlTexture();
				vect.push_back(pair);
				ServiceLocator::getGraphics().addToRenderMap(2, vect);
			}
			else if (input == 'N' || input == 'n')
			{
				run = false;
				break;
			}
		}
		catch (char c)
		{
			LOG(ERROR) << "Invalid input: " << c;
			continue;
		}

		SDL_RaiseWindow(ServiceLocator::getGraphics().getWindow()->getWindow());
		run = false;	
		break;
	}

	vect.clear();

}