#include "Square.h"
#include "SquareGraphicsComponent.h"

Square::Square() :
	_notation(""),
	_rect({0, 0, 125, 125}),
	_graphics(new SquareGraphicsComponent()),
	_occupied(false),
	_drawOverlay(false)
{}

Square::~Square()
{}