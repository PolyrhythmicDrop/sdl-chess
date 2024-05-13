#include "Square.h"
#include "ServiceLocator.h"
#include "easylogging++.h"

Square::Square(std::string notation) :
	_occupied(false),
	_graphics(new SquareGraphicsComponent()),
	_overlay(NONE),
	_tileType(DARK)
{
	_name = notation;
	_dimensions = {0, 0, 125, 125 };
	_zIndex = 1;
	_draw = false;
	_graphics->setSquareImgPath("images/squareSquare.png");
	_graphics->setOverlayImgPath("images/squareOverlay.png");
	_graphics->loadTexture();
	setMoveOverlayColor(81, 224, 240, 255);
	setTakeOverlayColor(240, 121, 81, 255);
	setLightTileColor(250, 237, 215, 255);
	setDarkTileColor(80, 59, 22, 255);
	setOverlayType(NONE);
	setTileType(DARK);
	_graphics->sumImage();
}

// Deep copy constructor
Square::Square(const Square& square)
{
	_name = square._name;
	_dimensions = square._dimensions;
	_zIndex = square._zIndex;
	_draw = square._draw;
	_occupied = square._occupied;
	_moveOverlayColor = square._moveOverlayColor;
	_takeOverlayColor = square._takeOverlayColor;
	_lightTileColor = square._lightTileColor;
	_darkTileColor = square._darkTileColor;
	_tileType = square._tileType;
	_graphics = new SquareGraphicsComponent();
	*_graphics = *(square._graphics);
	_overlay = square._overlay;

	LOG(INFO) << "Deep copy constructor called!";
}

Square& Square::operator=(const Square& other)
{
	LOG(INFO) << "Assignment operator called!";
	return *this;
}

Square::~Square()
{}

SquareGraphicsComponent* Square::getGraphicsComponent()
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
		SDL_SetTextureAlphaMod(_graphics->getOverlayTexture(), 0);
		break;
	case MOVE:
		SDL_SetTextureBlendMode(_graphics->getOverlayTexture(), SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(_graphics->getOverlayTexture(), 220);
		SDL_SetTextureColorMod(_graphics->getOverlayTexture(), _moveOverlayColor.r, _moveOverlayColor.g, _moveOverlayColor.b);
		break;
	case TAKE:
		SDL_SetTextureBlendMode(_graphics->getOverlayTexture(), SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(_graphics->getOverlayTexture(), 220);
		SDL_SetTextureColorMod(_graphics->getOverlayTexture(), _takeOverlayColor.r, _takeOverlayColor.g, _takeOverlayColor.b);
		break;
	}
	_graphics->sumImage();
	_overlay = overlay;
}

void Square::setLightTileColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	_lightTileColor = { r, g, b, a };
}

void Square::setDarkTileColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	_darkTileColor = { r, g, b, a };
}

void Square::setTileType(TileColor type)
{
	_tileType = type;
	if (_tileType == DARK)
	{
		SDL_SetTextureColorMod(_graphics->getSquareTexture(), _darkTileColor.r, _darkTileColor.g, _darkTileColor.b);
	}
	else
	{
		SDL_SetTextureColorMod(_graphics->getSquareTexture(), _lightTileColor.r, _lightTileColor.g, _lightTileColor.b);
	}
	_graphics->sumImage();
}