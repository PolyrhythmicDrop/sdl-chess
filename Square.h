#pragma once
#include "Piece.h"

class SquareGraphicsComponent;
class Chessboard;
class Piece;

// A square on the chessboard.
class Square : public GameObject
{
public:
	enum Overlay {
		NONE,
		MOVE,
		TAKE,
		CHECK,
		CASTLE
	};

	enum TileType {
		LIGHT,
		DARK
	};

	// Default constructor
	Square(std::string notation);
	// Deep copy constructor
	Square(const Square& square);
	// Copy assignment operator
	Square& operator=(const Square& other);

	// Move constructor
	Square(Square&& sq) noexcept;
	// Move assignment operator
	Square& operator=(Square&& sq) noexcept;

	~Square();

	SquareGraphicsComponent* getGraphicsComponent();

	/// <summary>
	/// Sets the square as occupied. Pass a piece to occupy it with that piece.
	/// </summary>
	/// <param name="occupied"></param>
	/// <param name="occupant"></param>
	void setOccupied(bool occupied = false, Piece* occupant = nullptr);


	inline bool getOccupied() const { return _occupied; };
	// Returns the piece that's on the square
	Piece* getOccupant();

	
	/// <summary>
	/// Gets the square's position on the board.
	/// </summary>
	/// <returns>Square's board index. First = row, second = column.</returns>
	inline std::pair<int, int> getBoardIndex() { return _boardIndex; };
	inline void setBoardIndex(int row, int column) { this->_boardIndex.first = row; this->_boardIndex.second = column; };

	// Overlay functions
	void setOverlayType(Overlay overlay);
	inline Overlay getOverlayType() const { return _overlay; };
	
	TileType getTileType();
	void setTileType(TileType type);

private:

	// True if the square is occupied, false if empty. If occupied, the square will use the take overlay. If empty, the square will use the move overlay.
	bool _occupied;
	// If occupied, the piece on the square
	Piece* _currentPiece;

	std::pair<int, int> _boardIndex;

	SquareGraphicsComponent* _graphics;

	Overlay _overlay;
	TileType _tileType;

};

