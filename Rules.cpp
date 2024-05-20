#include "Rules.h"
#include "Piece.h"


Rules::RulePackage Rules::getWhtPawnRules(Piece* piece)
{
	Rules::RulePackage pawnRules;

	// Set the move rules

	// If it is the pawn's first move, set the move distance to 2 columns. If not, set it to 1 column.
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

	// Determine whether or not the piece can attack en passant
	pawnRules.captureRules.enPassant = true;

	return pawnRules;
}
