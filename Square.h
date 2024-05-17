#pragma once
#include "Piece.h"

class SquareGraphicsComponent;
class Chessboard;
class Piece;

struct Color {
	Uint8 r, g, b, a;
};

// A square on the chessboard.
class Square : public GameObject
{
public:
	enum Overlay {
		NONE,
		MOVE,
		TAKE
	};

	enum TileType {
		LIGHT,
		DARK
	};

	// Default constructor
	Square(std::string name, Chessboard* board);
	// Deep copy constructor
	Square(const Square& square);
	// Assignment operator
	Square& operator=(const Square& other);

	~Square();

	SquareGraphicsComponent* getGraphicsComponent();

	// Sets and gets the square's occupied flag
	inline void setOccupied(bool occupied) { _occupied = occupied; };
	inline bool getOccupied() const { return _occupied; };
	// Returns the piece that's on the square
	Piece* getOccupant();

	// Overlay functions

	inline const Color* getMoveOverlayColor() { return &_moveOverlayColor; };
	inline const Color* getTakeOverlayColor() { return &_takeOverlayColor; };
	void setMoveOverlayColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void setTakeOverlayColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void setOverlayType(Overlay overlay);
	inline Overlay getOverlayType() const { return _overlay; };
	
	// Tile color functions

	inline const Color* getLightTileColor() const { return &_lightTileColor; };
	inline const Color* getDarkTileColor() const { return &_darkTileColor; };
	inline const TileType getTileType() const { return _tileType; };
	void setLightTileColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void setDarkTileColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	void setTileType(TileType type);

private:
	Chessboard* _chessboard;

	// True if the square is occupied, false if empty. If occupied, the square will use the take overlay. If empty, the square will use the move overlay.
	bool _occupied;
	// If occupied, the piece on the square
	Piece* _currentPiece;

	Color _moveOverlayColor;
	Color _takeOverlayColor;

	Color _lightTileColor;
	Color _darkTileColor;

	SquareGraphicsComponent* _graphics;

	Overlay _overlay;
	TileType _tileType;

};

