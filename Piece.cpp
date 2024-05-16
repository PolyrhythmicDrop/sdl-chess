#include "Piece.h"

Piece::Piece(Figure type, PieceColor color) :
	_type(type),
	_pieceColor(color),
	_selected(false),
	_alive(true),
	_position(nullptr),
	_graphics(std::unique_ptr<GraphicsComponent>(new GraphicsComponent)),
	_input(std::unique_ptr<PieceInputComponent>(new PieceInputComponent))
{
	changeType(type);
}

Piece::~Piece()
{}

void Piece::changeType(Figure type)
{
	_type = type;

	switch (_pieceColor)
	{
	case PieceColor::WHITE:
		switch (_type)
		{
		case Figure::PAWN:
			_graphics.get()->setImgPath("images/whtPawn.png");
			_graphics.get()->loadTexture();
			break;
		case Figure::BISHOP:
			_graphics.get()->setImgPath("images/whtBishop.png");
			_graphics.get()->loadTexture();
			break;
		case Figure::KNIGHT:
			_graphics.get()->setImgPath("images/whtKnight.png");
			_graphics.get()->loadTexture();
			break;
		case Figure::ROOK:
			_graphics.get()->setImgPath("images/whtRook.png");
			_graphics.get()->loadTexture();
			break;
		case Figure::QUEEN:
			_graphics.get()->setImgPath("images/whtQueen.png");
			_graphics.get()->loadTexture();
			break;
		case Figure::KING:
			_graphics.get()->setImgPath("images/whtKing.png");
			_graphics.get()->loadTexture();
			break;
		}
		break;
	case PieceColor::BLACK:
		switch (_type)
		{
		case Figure::PAWN:
			_graphics.get()->setImgPath("images/blkPawn.png");
			_graphics.get()->loadTexture();
			break;
		case Figure::BISHOP:
			_graphics.get()->setImgPath("images/blkBishop.png");
			_graphics.get()->loadTexture();
			break;
		case Figure::KNIGHT:
			_graphics.get()->setImgPath("images/blkKnight.png");
			_graphics.get()->loadTexture();
			break;
		case Figure::ROOK:
			_graphics.get()->setImgPath("images/blkRook.png");
			_graphics.get()->loadTexture();
			break;
		case Figure::QUEEN:
			_graphics.get()->setImgPath("images/blkQueen.png");
			_graphics.get()->loadTexture();
			break;
		case Figure::KING:
			_graphics.get()->setImgPath("images/blkKing.png");
			_graphics.get()->loadTexture();
			break;
		}
		break;
	}

}