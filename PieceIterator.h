#pragma once
#include <iterator>
#include "PieceContainer.h"

class Piece;
class PieceContainer;

class PieceIterator
{

	friend class PieceContainer;

private:

	PieceContainer* _pieceContainer;

	std::vector<Piece>::iterator _currentPosition;
	std::vector<Piece>::iterator _previousPosition;

	PieceIterator(PieceContainer* container);

	void updatePositions(std::vector<Piece>::iterator position);

public:

	std::vector<Piece>::iterator getCurrentPosition();
	std::vector<Piece>::iterator getPreviousPosition();

	void start();
	void forward(int num);
	void back(int num);

	int getIndex();
	void goToIndex(int index);

	int getSize();
	bool isDone();

};

