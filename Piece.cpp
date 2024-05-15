#include "Piece.h"

Piece::Piece(Figure type, PieceColor color) :
	_type(type),
	_pieceColor(color)
{}

Piece::~Piece()
{}

void Piece::changeType(Figure type)
{}