#pragma once
#include "GameObject.h"

class SquareGraphicsComponent;
class Chessboard;

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

	enum TileColor {
		LIGHT,
		DARK
	};

	// True if the square is occupied, false if empty. If occupied, the square will use the take overlay. If empty, the square will use the move overlay.
	bool _occupied;

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

	// Overlay functions

	inline const Color* getMoveOverlayColor() { return &_moveOverlayColor; };
	inline const Color* getTakeOverlayColor() { return &_takeOverlayColor; };
	void setMoveOverlayColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void setTakeOverlayColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void setOverlayType(Overlay overlay);
	inline Overlay getOverlayType() { return _overlay; };
	
	// Tile color functions

	inline const Color* getLightTileColor() { return &_lightTileColor; };
	inline const Color* getDarkTileColor() { return &_darkTileColor; };
	inline const TileColor getTileType() { return _tileType; };
	void setLightTileColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void setDarkTileColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	void setTileType(TileColor type);

private:
	Chessboard* _chessboard;

	Color _moveOverlayColor;
	Color _takeOverlayColor;

	Color _lightTileColor;
	Color _darkTileColor;

	SquareGraphicsComponent* _graphics;

	Overlay _overlay;
	TileColor _tileType;

};

