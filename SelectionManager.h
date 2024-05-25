#pragma once

class GameManager;
class Square;
class Piece;

class SelectionManager
{
friend class GameManager;
friend class HighlightManager;

private:

	std::shared_ptr<GameManager> _gm;

public:

	SelectionManager(GameManager* gm);
	~SelectionManager() {};

	/// <summary>
	///  Function template for the nested "for" loop that combs the BoardGrid by row and column. Use with a lambda: boardGridLoop([this](int row, int col) { your logic here });
	/// </summary>
	template<typename Func>
	void boardGridLoop(Func f);

	void handleClick();

	/// <summary>
	/// Handles a click on the board.
	/// </summary>
	void handleClickOnBoard(int x, int y);

	/// <summary>
	/// Handles a click on an empty square.
	/// </summary>
	/// <param name="square">The square that was clicked.</param>
	void handleClickOnEmptySquare(Square* square);

	/// <summary>
	/// Handles a click on a piece.
	/// </summary>
	/// <param name="piece">The piece that was clicked.</param>
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

