#pragma once

class Piece;

class Rules
{
public:

	struct MoveRules {

		// Can the piece move diagonally?
		bool diagMove = false;
		// Can the piece move orthoganally?
		bool orthoMove = false;
		// Can the piece jump over other pieces?
		bool jumpMove = false;
		// The number of rows this piece can move per turn. If bi-directional, use absolute value.
		int row = 0;
		// The number of columns this piece can move per turn. If bi-directional, use absolute value.
		int column = 0;
	};

	struct CaptureRules {
		// Can the piece capture en passant?
		bool enPassant = false;
		// Can the piece capture diagonally?
		bool diagCapture = false;
		// Can the piece capture orthoganally?
		bool orthoCapture = false;
		// Can the piece jump over other pieces to capture?
		bool jumpCapture = false;

		// The number of rows this piece can capture from per turn.
		int row = 0;
		// The number of columns this piece can capture from per turn.
		int column = 0;

	};

	struct SpecialActions {
		// Can the piece castle on this turn?
		bool castle = false;
		// Can the piece be promoted on this turn?
		bool promote = false;
	};

	struct RulePackage {
		MoveRules moveRules;
		CaptureRules captureRules;
		SpecialActions specialActions;
	};

	Rules() {};
	~Rules() {};

	// Determines which rules package to deliver
	Rules::RulePackage getRulesPackage(char fen, bool firstMove = false);

	// Uses a FEN name instead of a piece to determine the rules package to deliver.

	// Rules package for white pawns
	Rules::RulePackage getWhtPawnRules(bool firstMove = false);

	// Rules package for black pawns
	Rules::RulePackage getBlkPawnRules(bool firstMove = false);

	Rules::RulePackage getRookRules(bool firstMove = false);

	Rules::RulePackage getKnightRules(bool firstMove = false);

	Rules::RulePackage getBishopRules(bool firstMove = false);

	Rules::RulePackage getQueenRules(bool firstMove = false);

	Rules::RulePackage getKingRules(bool firstMove = false);



};

