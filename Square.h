#pragma once
#include "sdlfunc.h"
#include "GameObject.h"

// class SquareGraphicsComponent;

struct Color {
	Uint8 r, g, b, a;
};

// A square on the chessboard.
class Square : public GameObject
{

private:
	Color _moveOverlayColor;
	Color _takeOverlayColor;

public:
	// True if the square is occupied, false if empty. If occupied, the square will use the take overlay. If empty, the square will use the move overlay.
	bool _occupied;

	Square();
	~Square();

	// inline SquareGraphicsComponent* getGraphics() { return _graphics; };

	inline void setOccupied(bool occupied) { _occupied = occupied; };

	inline const Color* getMoveOverlayColor() { return &_moveOverlayColor; };
	inline const Color* getTakeOverlayColor() { return &_takeOverlayColor; };

	void setMoveOverlayColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void setTakeOverlayColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	void drawOverlay();



};

