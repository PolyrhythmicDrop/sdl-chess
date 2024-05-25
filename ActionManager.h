#pragma once
#include <memory>

class GameManager;
class Piece;
class Square;

class ActionManager
{
friend class GameManager;

private:

	std::shared_ptr<GameManager> _gm;

public:

	ActionManager(GameManager* gm) : _gm(gm) {};
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

	void captureEnPassant(Piece* attacker, Square* square);

	/// <summary>
	/// Promotes a pawn a different piece type once it reaches the opposite rank of the board.
	/// </summary>
	/// <param name="piece">The piece to promote.</param>
	void promotePawn(Piece* piece);
};

