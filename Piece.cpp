#include "Piece.h"
#include "Square.h"
#include "easylogging++.h"

Piece::Piece(Figure type, PieceColor color) :
	_type(type),
	_pieceColor(color),
	_fenName(' '),
	_selected(false),
	_alive(true),
	_firstMove(true),
	_passantable(false),
	_position(nullptr),
	_graphics(std::make_unique<PieceGraphicsComponent>()),
	_input(std::make_unique<PieceInputComponent>())
{
	changeType(type);
	LOG(TRACE) << "Piece Type: " << _type << " | Color: " << _pieceColor << " created!";
}

Piece::~Piece()
{
	LOG(TRACE) << "Piece Type: " << _type << " | Color: " << _pieceColor << " destroyed!";
}

// Deep Copy Constructor
Piece::Piece(const Piece& piece) :
	_pieceColor(piece._pieceColor)
{
	_mediator = piece._mediator;
	_position = piece._position;
	_passantable = piece._passantable;
	_type = piece._type;
	_fenName = piece._fenName;
	_name = piece._name;
	_selected = piece._selected;
	_alive = piece._alive;
	_firstMove = piece._firstMove;
	_input = std::make_unique<PieceInputComponent>();
	_graphics = std::make_unique<PieceGraphicsComponent>();

	LOG(DEBUG) << "Piece deep copy constructor called!";
}

// Copy assignment operator
Piece& Piece::operator=(const Piece& other)
{
	LOG(DEBUG) << "Piece copy assignment operator called!";
	return *this;
}

// Move constructor
Piece::Piece(Piece&& piece) noexcept :
	_position(nullptr),
	_pieceColor(piece._pieceColor),
	_type(piece._type),
	_fenName(piece._fenName),
	_firstMove(piece._firstMove),
	_passantable(piece._passantable),
	_selected(piece._selected),
	_alive(piece._alive),
	_input(std::make_unique<PieceInputComponent>()),
	_graphics(std::make_unique<PieceGraphicsComponent>())
{
	_mediator = piece._mediator;
	_name = piece._name;
	_dimensions = piece._dimensions;
	_position = piece._position;

	_input.swap(piece._input);
	_graphics.swap(piece._graphics);

	piece._input.reset();
	piece._graphics.reset();

	LOG(DEBUG) << "Piece move constructor called!";
}

// Move assignment operator
Piece& Piece::operator=(Piece&& piece) noexcept
{
	// Self-assignment detection
	if (&piece == this)
	{
		return *this;
	}

	// Reset any pointers
	_input.reset();
	_graphics.reset();
	delete _position;

	// Copy from the source object
	_position = piece._position;
	_pieceColor = piece._pieceColor;
	_type = piece._type;
	_fenName = piece._fenName;
	_firstMove = piece._firstMove;
	_passantable = piece._passantable;
	_selected = piece._selected;
	_alive = piece._alive;
	_input = std::make_unique<PieceInputComponent>();
	_input.swap(piece._input);
	_graphics = std::make_unique<PieceGraphicsComponent>();
	_graphics.swap(piece._graphics);

	_mediator = piece._mediator;
	_name = piece._name;
	_dimensions = piece._dimensions;	

	// Release any pointers from the source object
	piece._graphics.reset();
	piece._input.reset();
	delete piece._position;

	LOG(TRACE) << "Piece move assignment operator called!";

	return *this;
}

char const Piece::getFenName() const
{
	if (_fenName != NULL)
	{ 
		return _fenName; 
	}
	else
	{
		LOG(ERROR) << "Piece FEN name not found or not set!";
		return NULL;
	}
}

void Piece::setSquare(Square* square)
{
	if (square != nullptr)
	{
		if (square->getOccupant() == nullptr)
		{
			_position = square;
			_dimensions = *square->getDimensions();
			_graphics->setDrawDimByObjDim(_dimensions);
			square->setOccupied(true, this);
		}
		else
		{
			LOG(ERROR) << "Square currently occupied! Take the piece on the square first.";
		}
	}
	else
	{
		LOG(INFO) << "Piece removed from board!";
	}
}

Square* Piece::getSquare() const
{ 
	return _position;
}

void Piece::changeType(const Figure& type)
{
	_type = type;

	switch (_pieceColor)
	{
	case PieceColor::WHITE:
		switch (_type)
		{
		case Figure::PAWN:
			_graphics->setImgPath("assets/whtPawn.png");
			_graphics->loadTexture();
			setFenName('P');
			break;
		case Figure::BISHOP:
			_graphics->setImgPath("assets/whtBishop.png");
			_graphics->loadTexture();
			setFenName('B');
			break;
		case Figure::KNIGHT:
			_graphics->setImgPath("assets/whtKnight.png");
			_graphics->loadTexture();
			setFenName('N');
			break;
		case Figure::ROOK:
			_graphics->setImgPath("assets/whtRook.png");
			_graphics->loadTexture();
			setFenName('R');
			break;
		case Figure::QUEEN:
			_graphics->setImgPath("assets/whtQueen.png");
			_graphics->loadTexture();
			setFenName('Q');
			break;
		case Figure::KING:
			_graphics->setImgPath("assets/whtKing.png");
			_graphics->loadTexture();
			setFenName('K');
			break;
		}
		break;
	case PieceColor::BLACK:
		switch (_type)
		{
		case Figure::PAWN:
			_graphics->setImgPath("assets/blkPawn.png");
			_graphics->loadTexture();
			setFenName('p');
			break;
		case Figure::BISHOP:
			_graphics->setImgPath("assets/blkBishop.png");
			_graphics->loadTexture();
			setFenName('b');
			break;
		case Figure::KNIGHT:
			_graphics->setImgPath("assets/blkKnight.png");
			_graphics->loadTexture();
			setFenName('n');
			break;
		case Figure::ROOK:
			_graphics->setImgPath("assets/blkRook.png");
			_graphics->loadTexture();
			setFenName('r');
			break;
		case Figure::QUEEN:
			_graphics->setImgPath("assets/blkQueen.png");
			_graphics->loadTexture();
			setFenName('q');
			break;
		case Figure::KING:
			_graphics->setImgPath("assets/blkKing.png");
			_graphics->loadTexture();
			setFenName('k');
			break;
		}
		break;
	}

}

void Piece::setSelected(bool selected)
{
	_selected = selected;

	if (!_selected)
	{
		_graphics->removeSelectedIcon();

		if (_mediator != nullptr)
		{
			// Notify the GM that this piece was deselected.
			_mediator->notify(this, "pieceDeselected");
		}
	}
	else
	{
		_graphics->addSelectedIcon();

		if (_mediator != nullptr)
		{
			// Notify the GM that this piece was selected.
			_mediator->notify(this, "pieceSelected");
		}
	}
}

void Piece::setAlive(bool alive)
{
	_alive = alive;

	if (this->_mediator != nullptr)
	{
		alive ? _mediator->notify(this, "pieceRevived") : _mediator->notify(this, "pieceCaptured");
	}
	
}

void Piece::setFenName(char fen)
{
	_fenName = fen;
	std::string f{ fen };
	this->setName(f);
	this->_name;
}

void Piece::setPosition(int x, int y)
{
	_dimensions.x = x;
	_dimensions.y = y;

	_graphics->setDrawDimByObjDim(_dimensions);
}

