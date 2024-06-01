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
	_lightTileColor({ 255, 245, 207, 255 }),
	_darkTileColor({ 143, 132, 89, 255 }),
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
	_mediator = square._mediator;
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

void Square::setOccupied(bool occupy, Piece* occupant)
{
	// If the user tries to occupy the square with an occupant:
	if (occupant != nullptr)
	{
		// Check if the square is already occupied and that you want to occupy it
		if (_occupied == true && occupy == true)
		{
			LOG(ERROR) << "Square currently occupied! Capture the piece already on it before setting occupied.";
		}
		// If the square isn't occupied and you want to occupy it, set _occupied to true and set the supplied piece as the occupant.
		else if (_occupied == false && occupy == true)
		{
			_occupied = occupy;
			_currentPiece = occupant;
			_mediator->notify(this, "squareOccupied");
			LOG(INFO) << "Square " << _name << " occupied by " << occupant->getName();
		}
		else if (_occupied == true && occupy == false)
		{
			LOG(ERROR) << "Piece supplied as argument to setOccupied(), but occupy set to false.";
		}
		else if (_occupied == false && occupy == false)
		{
			LOG(ERROR) << "Square already unoccupied!";
		}
	}
	else
	{
		if (_occupied == true && occupy == true)
		{
			LOG(ERROR) << "Square already occupied, and no piece supplied!";
		}
		else if (_occupied == false && occupy == true)
		{
			LOG(INFO) << "Cannot occupy a square without a piece to occupy it! Please specify a piece.";
		}
		else if (_occupied == true && occupy == false)
		{
			_occupied = occupy;
			LOG(INFO) << "Piece moved from square " << _name << "!";
		}
		else if (_occupied == false && occupy == false)
		{
			LOG(INFO) << "Square already unoccupied!";
		}
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