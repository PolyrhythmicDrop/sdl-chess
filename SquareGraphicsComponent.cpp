/*

#include "SquareGraphicsComponent.h"
#include "ServiceLocator.h"
SquareGraphicsComponent::SquareGraphicsComponent() :
	_moveOverlayColor({ 81, 224, 240, 125 }),
	_takeOverlayColor({ 240, 121, 81, 125 })
{}

SquareGraphicsComponent::~SquareGraphicsComponent()
{}

void SquareGraphicsComponent::setMoveOverlayColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	_moveOverlayColor = { r, g, b, a };
}

void SquareGraphicsComponent::setTakeOverlayColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	_takeOverlayColor = { r, g, b, a };
}

/*
void SquareGraphicsComponent::drawOverlay(Square* square)
{
	SDL_Renderer* renderer = ServiceLocator::getGraphics().getRenderer()->GetRenderer();
	if (square->_drawOverlay = true)
	{
		if (square->_occupied = false)
		{
			SDL_SetRenderDrawColor(renderer, _moveOverlayColor.r, _moveOverlayColor.g, _moveOverlayColor.b, _moveOverlayColor.a);
			SDL_RenderFillRect(renderer, square->getRect());
		}
		else
		{
			SDL_SetRenderDrawColor(renderer, _takeOverlayColor.r, _takeOverlayColor.g, _takeOverlayColor.b, _takeOverlayColor.a);
			SDL_RenderFillRect(renderer, square->getRect());
		}
	}
	else
	{
		// If _drawOverlay is false, clear the rect
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderFillRect(renderer, square->getRect());
	}
}
*/