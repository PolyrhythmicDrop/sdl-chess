#include "Square.h"
#include "ServiceLocator.h"
#include "easylogging++.h"
#include "SquareGraphicsComponent.h"

Square::Square(std::string notation) :
	_occupied(false),
	_graphics(new SquareGraphicsComponent()),
	_tileType(DARK),
	_overlay(NONE)
{
	_name = notation;
	_dimensions = {0, 0, 125, 125 };
	_zIndex = 1;
	_draw = false;
	_graphics->setSquareImgPath("images/squareSquare.png");
	_graphics->setOverlayImgPath("images/square_Overlay.png");
	_graphics->loadTexture();
	setMoveOverlayColor(81, 224, 240, 255);
	setTakeOverlayColor(240, 121, 81, 255);
	setLightTileColor(240, 218, 225, 255);
	setDarkTileColor(70, 16, 33, 255);
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
	getGraphicsComponent()->sumImage(this);
}

void Square::setTakeOverlayColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	_takeOverlayColor = { r, g, b, a };
	getGraphicsComponent()->sumImage(this);
}

void Square::setOverlayType(Overlay overlay)
{
	_overlay = overlay;
	_graphics->sumImage(this);
}

void Square::setLightTileColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	_lightTileColor = { r, g, b, a };
	getGraphicsComponent()->sumImage(this);
}

void Square::setDarkTileColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	_darkTileColor = { r, g, b, a };
	getGraphicsComponent()->sumImage(this);
}

void Square::setTileType(TileColor type)
{
	_tileType = type;
	getGraphicsComponent()->sumImage(this);
}