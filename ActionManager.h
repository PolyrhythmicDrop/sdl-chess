#pragma once
#include <memory>

class GameManager;
class Piece;
class Square;

class ActionManager
{
friend class GameManager;

protected:

	struct UndoValues {
		bool firstMove = NULL;
		bool alive = NULL;
		bool passantable = NULL;
		Square* square = nullptr;
		~UndoValues() {};
	};

	struct UndoBuffer {
		UndoValues* attacker;
		UndoValues* defender;
	};

private:

	std::shared_ptr<GameManager> _gm;
	
	UndoBuffer _undoBuffer;

public:

	ActionManager(GameManager* gm);
	~ActionManager() {};

	/// <summary>
	/// Moves a piece to the target square.
	/// </summary>
	/// <param name="piece">The piece to move.</param>
	/// <param name="target">The square to move to.</param>
	void movePiece(Piece* piece, Square* target);

	/// <summary>
	/// Captures the specified piece.
	/// </summary>
	/// <param name="attacker">The piece that is capturing.</param>
	/// <param name="defender">The piece to be captured.</param>
	void capturePiece(Piece* attacker, Piece* defender);

	/// <summary>
	/// Captures a pawn _en passant_. 
	/// Only available if the piece's "passantable" flag is true, and certain other factors are met.
	/// </summary>
	/// <param name="attacker">The capturing piece.</param>
	/// <param name="square">The square the capturing piece will move to after capture.</param>
	void captureEnPassant(Piece* attacker, Square* square);

	/// <summary>
	/// Promotes a pawn to a different piece type once it reaches the opposite rank of the board.
	/// </summary>
	/// <param name="piece">The piece to promote.</param>
	void promotePawn(Piece* piece);

	/// <summary>
	/// Performs a castle move with the king and the nearest rook.
	/// </summary>
	/// <param name="king">The king to castle with.</param>
	/// <param name="square">The square the king should move to.</param>
	void castleKing(Piece* king, Square* square);

	// ** Undo Funtions **

	void addToUndoBuffer(Piece* attacker = nullptr, Piece* defender = nullptr);
	UndoBuffer getUndoBuffer();
	void clearUndoBuffer();
	void undoAction(Piece* attacker = nullptr, Piece* defender = nullptr);

};

