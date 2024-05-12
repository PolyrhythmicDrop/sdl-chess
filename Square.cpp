#include "Square.h"
#include "ServiceLocator.h"

Square::Square() :
	_occupied(false),
	_moveOverlayColor({ 81, 224, 240, 125 }),
	_takeOverlayColor({ 240, 121, 81, 125 })
{
	_name = "";
	_dimensions = {0, 0, 125, 125 };
	_zIndex = 0;
	_draw = false;
}

Square::~Square()
{}

void Square::setMoveOverlayColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	_moveOverlayColor = { r, g, b, a };
}

void Square::setTakeOverlayColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	_takeOverlayColor = { r, g, b, a };
}

void Square::drawOverlay()
{
	SDL_Renderer* renderer = ServiceLocator::getGraphics().getRenderer()->GetRenderer();
	if (_draw = true)
	{
		if (_occupied = false)
		{
			SDL_SetRenderDrawColor(renderer, _moveOverlayColor.r, _moveOverlayColor.g, _moveOverlayColor.b, _moveOverlayColor.a);
			SDL_RenderFillRect(renderer, getDimensions());
		}
		else
		{
			SDL_SetRenderDrawColor(renderer, _takeOverlayColor.r, _takeOverlayColor.g, _takeOverlayColor.b, _takeOverlayColor.a);
			SDL_RenderFillRect(renderer, getDimensions());
		}
	}
	else
	{
		// If _draw is false, clear the rect
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderFillRect(renderer, getDimensions());
	}
}