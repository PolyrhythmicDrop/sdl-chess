#include "Rules.h"
#include "Piece.h"
#include "Square.h"
#include "easylogging++.h"

Rules::RulePackage Rules::getRulesPackage(char fen, bool firstMove)
{
	RulePackage rules;

	// Get the type of piece on the square and determine which rule evaluation set to use on it.
	switch (fen)
	{
	case 'P':
	case 'p':
		rules = getPawnRules(firstMove);
		break;
	case 'R': 
	case 'r':
		rules = getRookRules(firstMove);
		break;
	case 'N':
	case 'n':
		rules = getKnightRules(firstMove);
		break;
	case 'B':
	case 'b':
		rules = getBishopRules(firstMove);
		break;
	case 'Q':
	case 'q':
		rules = getQueenRules(firstMove);
		break;
	case 'K':
	case 'k':
		rules = getKingRules(firstMove);
		break;
	default:
		LOG(ERROR) << "Piece name doesn't match any FEN value! Rules not packaged.";
		break;
	}

	return rules;
}

Rules::RulePackage Rules::getPawnRules(bool firstMove)
{
	Rules::RulePackage pawnRules;

	// Set the move rules
	// ******************
	pawnRules.moveRules.orthoMove = true;

	// If it is the pawn's first move, set the move distance to 2 columns. If not, set it to 1 row.
	if (firstMove == true)
	{
		pawnRules.moveRules.row = 2;
		pawnRules.moveRules.column = 0;
	}
	else
	{
		pawnRules.moveRules.row = 1;
		pawnRules.moveRules.column = 0;
	}

	// Set the capture rules
	// **********************

	pawnRules.captureRules.diagCapture = true;
	pawnRules.captureRules.row = 1;
	pawnRules.captureRules.column = 1;

	// Determine whether or not the piece can attack en passant
	pawnRules.captureRules.enPassant = true;

	// Set the special rules
	// ***********************

	// Set whether the piece can be promoted
	pawnRules.specialActions.promote = true;

	return pawnRules;
}

Rules::RulePackage Rules::getRookRules(bool firstMove)
{
	Rules::RulePackage rookRules;

	// Set the move rules
	// ******************

	rookRules.moveRules.orthoMove = true;
	rookRules.moveRules.row = 7;
	rookRules.moveRules.column = 7;

	// Set the capture rules
	// **********************

	rookRules.captureRules.orthoCapture = true;
	rookRules.captureRules.row = 6;
	rookRules.captureRules.column = 6;

	// Set the special rules
	// ***********************

	// Set rules for castling?

	return rookRules;

}

Rules::RulePackage Rules::getKnightRules(bool firstMove)
{
	Rules::RulePackage knightRules;

	// Set the move rules
	// ******************

	knightRules.moveRules.jumpMove = true;
	knightRules.moveRules.row = 2;
	knightRules.moveRules.column = 2;


	// Set the capture rules
	// ******************

	knightRules.captureRules.jumpCapture = true;
	knightRules.captureRules.row = 2;
	knightRules.captureRules.column = 2;


	return knightRules;

}

Rules::RulePackage Rules::getBishopRules(bool firstMove)
{
	Rules::RulePackage bishopRules;

	// Set the move rules
	// ******************

	bishopRules.moveRules.diagMove = true;
	bishopRules.moveRules.row = 7;
	bishopRules.moveRules.column = 7;

	// Set the capture rules
	// **********************

	bishopRules.captureRules.diagCapture = true;
	bishopRules.captureRules.row = 7;
	bishopRules.captureRules.column = 7;


	return bishopRules;
}

Rules::RulePackage Rules::getQueenRules(bool firstMove)
{
	Rules::RulePackage queenRules;

	// Set the move rules
	// ******************

	queenRules.moveRules.diagMove = true;
	queenRules.moveRules.orthoMove = true;
	queenRules.moveRules.row = 7;
	queenRules.moveRules.column = 7;

	// Set the capture rules
	// **********************

	queenRules.captureRules.diagCapture = true;
	queenRules.captureRules.orthoCapture = true;
	queenRules.captureRules.row = 7;
	queenRules.captureRules.column = 7;


	return queenRules;
}

Rules::RulePackage Rules::getKingRules(bool firstMove)
{
	Rules::RulePackage kingRules;

	// Set the move rules
	// ******************

	kingRules.moveRules.diagMove = true;
	kingRules.moveRules.orthoMove = true;
	kingRules.moveRules.row = 1;
	kingRules.moveRules.column = 1;

	// Set the capture rules
	// **********************

	kingRules.captureRules.diagCapture = true;
	kingRules.captureRules.orthoCapture = true;
	kingRules.captureRules.row = 1;
	kingRules.captureRules.column = 1;

	// Set the special rules
	// **********************

	kingRules.specialActions.castle = true;


	return kingRules;
}
