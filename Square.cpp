#include "Square.h"
#include "ServiceLocator.h"
#include "easylogging++.h"
#include "SquareGraphicsComponent.h"
#include "Chessboard.h"

Square::Square(std::string notation, Chessboard* board) :
	_occupied(false),
	_graphics(new SquareGraphicsComponent()),
	_tileType(DARK),
	_overlay(NONE),
	_moveOverlayColor({ 81, 224, 240, 255 }),
	_takeOverlayColor({ 240, 121, 81, 255 }),
	_lightTileColor({ 240, 218, 225, 255 }),
	_darkTileColor({ 70, 16, 33, 255 }),
	_chessboard(board),
	_currentPiece(nullptr)
{
	_name = notation;
	_dimensions = {0, 0, this->_chessboard->getDimensions()->w / 8, this->_chessboard->getDimensions()->h / 8 };
	_zIndex = 1;
	_draw = false;
	_graphics->setOverlayImgPath("images/square_Overlay.png");
	_graphics->loadTexture(this);
	_graphics->sumImage(this);
}

// Deep copy constructor
Square::Square(const Square& square)
{
	_name = square._name;
	_dimensions = square._dimensions;
	_zIndex = square._zIndex;
	_draw = square._draw;
	_occupied = square._occupied;
	_boardIndex = square._boardIndex;
	_currentPiece = square._currentPiece;
	_moveOverlayColor = square._moveOverlayColor;
	_takeOverlayColor = square._takeOverlayColor;
	_lightTileColor = square._lightTileColor;
	_darkTileColor = square._darkTileColor;
	_tileType = square._tileType;
	_graphics = new SquareGraphicsComponent();
	*_graphics = *(square._graphics);
	_chessboard = (square._chessboard);
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

void Square::setOccupied(bool occupied, Piece* occupant)
{
	if (_occupied != occupied)
	{
		_occupied = occupied;
		_currentPiece = occupant;
	}
	else
	{
		LOG(TRACE) << "Square already occupied! Perform a Take move first.";
	}
}

Piece* Square::getOccupant()
{
	if (_occupied)
	{
		return _currentPiece;
	}
	else
	{
		return nullptr;
	}

}

void Square::setMoveOverlayColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	_moveOverlayColor = { r, g, b, a };
	_graphics->sumImage(this);
}

void Square::setTakeOverlayColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	_takeOverlayColor = { r, g, b, a };
	_graphics->sumImage(this);
}

void Square::setOverlayType(Overlay overlay)
{
	_overlay = overlay;
	_graphics->sumImage(this);
}

void Square::setLightTileColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	_lightTileColor = { r, g, b, a };
}

void Square::setDarkTileColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	_darkTileColor = { r, g, b, a };
	getGraphicsComponent()->sumImage(this);
}

void Square::setTileType(TileType type)
{
	_tileType = type;
	getGraphicsComponent()->sumImage(this);
}