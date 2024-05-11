#pragma once
#include "sdlfunc.h"


class SquareGraphicsComponent;

// A square on the chessboard.
class Square
{
	friend SquareGraphicsComponent;

private:

	SDL_Rect _rect;

	SquareGraphicsComponent* _graphics;

public:
	// True if the square is occupied, false if empty. If occupied, the square will use the take overlay. If empty, the square will use the move overlay.
	bool _occupied;
	// Whether or not to render the overlay. Usually false, unless a piece is selected.
	bool _drawOverlay;
	// Chess notation of the square
	std::string _notation;

	Square();
	~Square();

	inline const std::string* getNotation() { return &_notation; };

	inline const SDL_Rect* getRect() { return &_rect; };

	inline SquareGraphicsComponent* getGraphics() { return _graphics; };

	inline void setPos(int x, int y) { _rect.x = x; _rect.y = y; };

	inline void setOccupied(bool occupied) { _occupied = occupied; };



};

