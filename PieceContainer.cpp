#include "PieceContainer.h"
#include "PieceIterator.h"

PieceContainer::PieceContainer() :
	_pieces(),
	_capturedPieces({})
{}

PieceIterator PieceContainer::createIterator()
{
	PieceIterator pieceItr(this);
	return pieceItr;
}