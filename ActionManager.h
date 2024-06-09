#pragma once
#include <memory>
#include <optional>

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
	/// Captures the specified piece.
	/// </summary>
	/// <param name="attacker">The piece that is capturing.</param>
	/// <param name="defender">The piece to be captured.</param>
	void capturePiece(Piece* attacker, Piece* defender, bool passant = false, std::optional<Square*> passantSq = std::nullopt);

	/// <summary>
	/// Captures a pawn _en passant_. 
	/// Only available if the piece's "passantable" flag is true, and certain other factors are met.
	/// </summary>
	/// <param name="attacker">The capturing piece.</param>
	/// <param name="square">The square the capturing piece will move to after capture.</param>
	void captureEnPassant(Piece* attacker, Square* square);

	/// <summary>
	/// Moves a piece to the target square.
	/// </summary>
	/// <param name="piece">The piece to move.</param>
	/// <param name="target">The square to move to.</param>
	void movePiece(Piece* piece, Square* target);

	// Check to see if an action is a valid one.
	bool testAction(Piece* piece);

	// Actions that take place after a piece's first move
	void postFirstMove(Piece* piece, std::pair<int, int> moveDistance, Square* srcSq);

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

	/// <summary>
	/// Disables the FEN castle modifier on rook/king move or rook capture
	/// </summary>
	/// <param name="piece">The piece that moved or was captured</param>
	/// <param name="kingside">True if the kingside rook moved or was captured, false if queenside rook moved or was captured, nullopt if the king moved</param>
	void disableFenCastle(bool capture = false, std::optional<bool> kingside = std::nullopt);

	void postMove(Piece* piece, Square* srcSq, Square* tarSq);

	// ** Undo Functions **

	void addToUndoBuffer(Piece* attacker = nullptr, Piece* defender = nullptr);
	UndoBuffer getUndoBuffer();
	void clearUndoBuffer();
	void undoAction(Piece* attacker = nullptr, Piece* defender = nullptr);

};

