#include "Rules.h"
#include "Piece.h"
#include "Square.h"


Rules::RulePackage Rules::getWhtPawnRules(Piece* piece)
{
	Rules::RulePackage pawnRules;

	// Set the move rules
	// ******************
	
	// If it is the pawn's first move, set the move distance to 2 columns. If not, set it to 1 row.
	if (piece->getFirstMove() == true)
	{
		pawnRules.moveDistance.row = 2;
		pawnRules.moveDistance.column = 0;
	}
	else
	{
		pawnRules.moveDistance.row = 1;
		pawnRules.moveDistance.column = 0;
	}

	// Set the capture rules
	// **********************

	pawnRules.captureRules.diagCapture = true;
	pawnRules.captureRules.captureDistance = 1;

	// Determine whether or not the piece can attack en passant
	pawnRules.captureRules.enPassant = true;

	// Set the special rules
	// ***********************
	
	// Set whether the piece can be promoted
	// If the piece is in its same column and it has reached the last square in the board, it can be promoted.
	if (piece->getPosition()->getBoardIndex().second == piece->getPosition()->getBoardIndex().second 
		&& piece->getPosition()->getBoardIndex().first == 7)
	{
		pawnRules.specialActions.promote = true;
	}

	return pawnRules;
}
