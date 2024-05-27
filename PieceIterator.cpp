#include "PieceIterator.h"

PieceIterator::PieceIterator(PieceContainer* container) :
	_pieceContainer(container),
	_currentPosition(_pieceContainer->_pieces.begin()),
	_previousPosition(_currentPosition)
{}


void PieceIterator::updatePositions(std::vector<Piece>::iterator position)
{
	_previousPosition = _currentPosition;
	_currentPosition = position;
}

std::vector<Piece>::iterator PieceIterator::getCurrentPosition()
{
	return _currentPosition;
}

std::vector<Piece>::iterator PieceIterator::getPreviousPosition()
{
	return _previousPosition;
}

std::vector<Piece>::iterator PieceIterator::getContainerBegin()
{
	return _pieceContainer->_pieces.begin();
}

std::vector<Piece>::iterator PieceIterator::getContainerEnd()
{
	return _pieceContainer->_pieces.end();
}

void PieceIterator::goToStart()
{
	updatePositions(_pieceContainer->_pieces.begin());
}

void PieceIterator::goForward(int num)
{
	updatePositions(std::next(_currentPosition, num));
}

void PieceIterator::goBack(int num)
{
	updatePositions(std::prev(_currentPosition, num));
}

void PieceIterator::goToEnd()
{
	updatePositions(_pieceContainer->_pieces.end());
}

int PieceIterator::getIndex()
{
	return std::distance(_pieceContainer->_pieces.begin(), _currentPosition);
}

void PieceIterator::goToIndex(int index)
{
	updatePositions(_pieceContainer->_pieces.begin() + index);
}

int PieceIterator::getSize()
{
	return _pieceContainer->_pieces.size();
}

bool PieceIterator::isDone()
{
	return _currentPosition == _pieceContainer->_pieces.end();
}

