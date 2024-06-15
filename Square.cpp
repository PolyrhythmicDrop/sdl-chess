#include "Square.h"
#include "easylogging++.h"
#include "SquareGraphicsComponent.h"


Square::Square(std::string notation) :
	_occupied(false),
	_graphics(std::make_unique<SquareGraphicsComponent>()),
	_tileType(DARK),
	_overlay(NONE),
	_currentPiece(nullptr)
{
	_name = notation;
	_zIndex = 1;
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
	_tileType = square._tileType;
	_graphics = std::make_unique<SquareGraphicsComponent>();
	
	_overlay = square._overlay;

	LOG(INFO) << "Deep copy constructor called!";
}

Square& Square::operator=(const Square& other)
{
	LOG(INFO) << "Assignment operator called!";
	return *this;
}

// Move constructor
Square::Square(Square&& sq) noexcept :
	_occupied(sq._occupied),
	_boardIndex(sq._boardIndex),
	_currentPiece(sq._currentPiece),
	_tileType(sq._tileType),
	_overlay(sq._overlay),
	_graphics(std::make_unique<SquareGraphicsComponent>())
{
	_mediator = sq._mediator;
	_name = sq._name;
	_dimensions = sq._dimensions;
	_zIndex = sq._zIndex;
	_draw = sq._draw;
	_graphics.swap(sq._graphics);

	// Reset the passed unique ptr
	sq._graphics.reset();

	LOG(TRACE) << "Square move constructor called!";
}

// Move assignment operator
Square& Square::operator=(Square&& sq) noexcept
{
	// Self-assignment detection
	if (&sq == this)
	{
		return *this;
	}

	// Delete any pointers
	_graphics.reset();
	delete _currentPiece;

	// Copy from the source object
	_mediator = sq._mediator;
	_name = sq._name;
	_dimensions = sq._dimensions;
	_zIndex = sq._zIndex;
	_draw = sq._draw;
	_occupied = sq._occupied;
	_boardIndex = sq._boardIndex;
	_currentPiece = sq._currentPiece;
	_tileType = sq._tileType;
	_graphics = std::make_unique<SquareGraphicsComponent>();
	_graphics.swap(sq._graphics);
	_overlay = sq._overlay;

	// Release any pointers from the source object
	sq._currentPiece = nullptr;
	sq._graphics.reset();

	LOG(TRACE) << "Square move assignment operator called!";

	return *this;

}

Square::~Square()
{}

SquareGraphicsComponent* Square::getGraphicsComponent()
{
	return _graphics.get();
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

const std::pair<int, int> Square::getBoardIndex() const
{ 
	return _boardIndex;
}

void Square::setBoardIndex(int row, int column) 
{ 
	_boardIndex.first = row;
	_boardIndex.second = column;
}

void Square::setOverlayType(const Overlay& overlay)
{
	_overlay = overlay;
	_graphics->sumImage(this);
}

const Square::Overlay& Square::getOverlayType() const
{ 
	return _overlay;
}

void Square::setTileType(const TileType& type)
{
	_tileType = type;
	_graphics->sumImage(this);
}

const Square::TileType& Square::getTileType() const
{ 
	return _tileType; 
}

void Square::setPosition(int x, int y)
{
	_dimensions.x = x;
	_dimensions.y = y;

	_graphics->setDrawDimByObjDim(_dimensions);
}