#include "Square.h"
#include "ServiceLocator.h"

Square::Square(std::string notation) :
	_occupied(false),
	_moveOverlayColor({ 81, 224, 240, 125 }),
	_takeOverlayColor({ 240, 121, 81, 125 }),
	_graphics(new GraphicsComponent()),
	_overlay(NONE)
{
	_name = notation;
	_dimensions = {0, 0, 125, 125 };
	_zIndex = 1;
	_draw = false;
	_graphics->setImgPath("images/squareOverlay.png");
	_graphics->loadTexture();
	setMoveOverlayColor(81, 224, 240, 255);
	setTakeOverlayColor(240, 121, 81, 255);
	setOverlayType(NONE);
}

Square::~Square()
{}

GraphicsComponent* Square::getGraphicsComponent()
{
	return _graphics;
}

void Square::setMoveOverlayColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	_moveOverlayColor = { r, g, b, a };
}

void Square::setTakeOverlayColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	_takeOverlayColor = { r, g, b, a };
}

void Square::setOverlayType(Overlay overlay)
{
	switch (overlay)
	{
	case NONE:
		SDL_SetTextureAlphaMod(_graphics->getSdlTexture(), 0);
		break;
	case MOVE:
		SDL_SetTextureBlendMode(_graphics->getSdlTexture(), SDL_BLENDMODE_ADD);
		SDL_SetTextureAlphaMod(_graphics->getSdlTexture(), 200);
		SDL_SetTextureColorMod(_graphics->getSdlTexture(), _moveOverlayColor.r, _moveOverlayColor.g, _moveOverlayColor.b);
		break;
	case TAKE:
		SDL_SetTextureBlendMode(_graphics->getSdlTexture(), SDL_BLENDMODE_ADD);
		SDL_SetTextureAlphaMod(_graphics->getSdlTexture(), 200);
		SDL_SetTextureColorMod(_graphics->getSdlTexture(), _takeOverlayColor.r, _takeOverlayColor.g, _takeOverlayColor.b);
		break;
	}
	_overlay = overlay;
}

/*
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
*/