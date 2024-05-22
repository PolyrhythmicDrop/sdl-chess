#include "ActionManager.h"
#include "GameManager.h"
#include "GameScene.h"

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
}

void ActionManager::capturePiece(Piece* attacker, Piece* defender)
{
	Square* defPos = defender->getSquare();
	// De-occupy the defender's square
	defPos->setOccupied(false);
	// Unalive the defender
	defender->setAlive(false);
	// Move the attacking piece into the defender's position
	movePiece(attacker, defPos);
	// Set the defender's position to null
	defender->setSquare(nullptr);
	// Add the defender to the captured piece location
	_gm->_gameScene->addToCapturedPieces(defender);
}