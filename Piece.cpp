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
	_graphics(new PieceGraphicsComponent),
	_input(new PieceInputComponent)
{
	changeType(type);
	LOG(TRACE) << "Piece Type: " << _type << " | Color: " << _pieceColor << " created!";
}

// Deep Copy Constructor
Piece::Piece(const Piece& piece)
{
	_mediator = piece._mediator;
	_position = piece._position;
	_passantable = piece._passantable;
	_pieceColor = piece._pieceColor;
	_type = piece._type;
	_fenName = piece._fenName;
	_name = piece._name;
	_selected = piece._selected;
	_alive = piece._alive;
	_firstMove = piece._firstMove;
	_input = piece._input;
	_graphics = new PieceGraphicsComponent();
	*_graphics = *(piece._graphics);
	LOG(TRACE) << "Piece deep copy constructor called!";
}

Piece::~Piece()
{
	LOG(TRACE) << "Piece Type: " << _type << " | Color: " << _pieceColor << " destroyed!";
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
			square->setOccupied(true, this);
			// Notify the GameManager that the position has changed.
			if (_mediator != nullptr)
			{
				this->_mediator->notify(this, "pieceMove");
			}
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

void Piece::changeType(Figure type)
{
	_type = type;

	switch (_pieceColor)
	{
	case PieceColor::WHITE:
		switch (_type)
		{
		case Figure::PAWN:
			_graphics->setImgPath("images/whtPawn.png");
			_graphics->loadTexture(this);
			setFenName('P');
			break;
		case Figure::BISHOP:
			_graphics->setImgPath("images/whtBishop.png");
			_graphics->loadTexture(this);
			setFenName('B');
			break;
		case Figure::KNIGHT:
			_graphics->setImgPath("images/whtKnight.png");
			_graphics->loadTexture(this);
			setFenName('N');
			break;
		case Figure::ROOK:
			_graphics->setImgPath("images/whtRook.png");
			_graphics->loadTexture(this);
			setFenName('R');
			break;
		case Figure::QUEEN:
			_graphics->setImgPath("images/whtQueen.png");
			_graphics->loadTexture(this);
			setFenName('Q');
			break;
		case Figure::KING:
			_graphics->setImgPath("images/whtKing.png");
			_graphics->loadTexture(this);
			setFenName('K');
			break;
		}
		break;
	case PieceColor::BLACK:
		switch (_type)
		{
		case Figure::PAWN:
			_graphics->setImgPath("images/blkPawn.png");
			_graphics->loadTexture(this);
			setFenName('p');
			break;
		case Figure::BISHOP:
			_graphics->setImgPath("images/blkBishop.png");
			_graphics->loadTexture(this);
			setFenName('b');
			break;
		case Figure::KNIGHT:
			_graphics->setImgPath("images/blkKnight.png");
			_graphics->loadTexture(this);
			setFenName('n');
			break;
		case Figure::ROOK:
			_graphics->setImgPath("images/blkRook.png");
			_graphics->loadTexture(this);
			setFenName('r');
			break;
		case Figure::QUEEN:
			_graphics->setImgPath("images/blkQueen.png");
			_graphics->loadTexture(this);
			setFenName('q');
			break;
		case Figure::KING:
			_graphics->setImgPath("images/blkKing.png");
			_graphics->loadTexture(this);
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
		_graphics->removeSelectedIcon(this);

		if (this->_mediator != nullptr)
		{
			// Notify the GM that this piece was deselected.
			this->_mediator->notify(this, "pieceDeselected");
		}
	}
	else
	{
		_graphics->addSelectedIcon(this);

		if (this->_mediator != nullptr)
		{
			// Notify the GM that this piece was selected.
			this->_mediator->notify(this, "pieceSelected");
		}
	}
}

void Piece::setFenName(char fen)
{
	_fenName = fen;
	std::string f{ fen };
	this->setName(f);
	this->_name;
}

