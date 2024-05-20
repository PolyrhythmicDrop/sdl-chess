#pragma once

class Piece;

class Rules
{
public:

	struct MoveDistance {
		// The number of rows this piece is allowed to move on this turn.
		int row;

		// The number of columns this piece is allowed to move on this turn.
		int column;
	};

	struct CaptureRules {
		// Can the piece capture en passant on this turn?
		bool enPassant = false;
	};

	struct SpecialActions {
		// Can the piece castle on this turn?
		bool castle = false;
		// Can the piece be promoted on this turn?
		bool promote = false;
		// Can the piece jump over other pieces?
		bool jumpPieces = false;
	};

	struct RulePackage {
		MoveDistance moveDistance;
		CaptureRules captureRules;
		SpecialActions specialActions;
	};

	Rules() {};
	~Rules() {};

	RulePackage getWhtPawnRules(Piece* piece);

};

