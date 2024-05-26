#pragma once
#include <vector>
#include "Piece.h"

class PieceIterator;

class PieceContainer
{
	friend class PieceIterator;

private:

	std::vector<Piece> _pieces;

	// Captured pieces go here.
	// Key is the color of the piece. 0 = Black, 1 = White.
	std::map<int, std::vector<Piece*>> _capturedPieces;

public:

	PieceContainer();
	~PieceContainer() {};

	PieceIterator createIterator();


};

