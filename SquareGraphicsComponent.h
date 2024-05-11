#pragma once
#include "Square.h"

struct Color {
	Uint8 r, g, b, a;
};

class SquareGraphicsComponent
{
protected:

	Color _moveOverlayColor;
	Color _takeOverlayColor;

public:

	SquareGraphicsComponent();
	~SquareGraphicsComponent();

	inline const Color* getMoveOverlayColor() { return &_moveOverlayColor; };
	inline const Color* getTakeOverlayColor() { return &_takeOverlayColor; };

	void setMoveOverlayColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void setTakeOverlayColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	void drawOverlay(Square* square);

};

