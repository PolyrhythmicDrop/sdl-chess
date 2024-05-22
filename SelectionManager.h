#pragma once

class GameManager;
class Square;
class Piece;

class SelectionManager
{
friend class GameManager;

private:

	GameManager* _gm;

public:

	SelectionManager(GameManager* gm) : _gm(gm) {};
	~SelectionManager() {};

	/// <summary>
	///  Function template for the nested "for" loop that combs the BoardGrid by row and column. Use with a lambda: boardGridLoop([this](int row, int col) { your logic here });
	/// </summary>
	template<typename Func>
	void boardGridLoop(Func f);

	void handleClick();

	/// <summary>
	/// Handles a click on a square and calls different functions, depending on what was clicked and in what context.
	/// </summary>
	void handleClickOnBoard(int x, int y);

	void handleClickOnEmptySquare(Square* square);

	void handleClickOnPiece(Piece* piece);

	/// <summary>
	/// Selects a specific piece.
	/// </summary>
	/// <param name="piece">The piece to select.</param>
	void selectPiece(Piece* piece);

	/// <summary>
	/// Deselects all selected pieces on the board.
	/// </summary>
	/// <param name="exception">Deselects all pieces but this one. Optional field.</param>
	void deselectPieces(Piece* exception = nullptr);
};

