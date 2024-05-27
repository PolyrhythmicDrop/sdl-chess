#include "BoardIterator.h"


BoardIterator::BoardIterator(Chessboard* board) :
	_board(board),
	_currentRowPos(_board->getBoardGrid()->begin()),
	_prevRowPos(_currentRowPos),
	_currentColPos(_board->getBoardGrid()->at(0).begin()),
	_prevColPos(_currentColPos)
{}


void BoardIterator::updatePositions(std::vector<std::vector<Square>>::iterator rowPosition, std::vector<Square>::iterator colPosition)
{
	updateRowPos(rowPosition);
	updateColPos(colPosition);
}

void BoardIterator::updateRowPos(std::vector<std::vector<Square>>::iterator rowPosition)
{
	_prevRowPos = _currentRowPos;
	_currentRowPos = rowPosition;
}

void BoardIterator::updateColPos(std::vector<Square>::iterator colPosition)
{
	_prevColPos = _currentColPos;
	_currentColPos = colPosition;
}

std::vector<std::vector<Square>>::iterator BoardIterator::getCurrentRowPos()
{
	return _currentRowPos;
}

std::vector<std::vector<Square>>::iterator BoardIterator::getPrevRowPos()
{
	return _prevRowPos;
}

std::vector<Square>::iterator BoardIterator::getCurrentColPos()
{
	return _currentColPos;
}

std::vector<Square>::iterator BoardIterator::getPrevColPos()
{
	return _prevColPos;
}

std::vector<std::vector<Square>>::iterator BoardIterator::getFirstRow()
{
	return _board->getBoardGrid()->begin();
}

std::vector<std::vector<Square>>::iterator BoardIterator::getLastRow()
{
	return _board->getBoardGrid()->end();
}

std::vector<Square>::iterator BoardIterator::getFirstColumn(int row)
{
	return _board->getBoardGrid()->at(row).begin();
}

std::vector<Square>::iterator BoardIterator::getLastColumn(int row)
{
	return _board->getBoardGrid()->at(row).end();
}

void BoardIterator::goToStart()
{
	updatePositions(_board->getBoardGrid()->begin(), _board->getBoardGrid()->at(0).begin());
}

void BoardIterator::goToEnd()
{
	updatePositions(_board->getBoardGrid()->end(), _board->getBoardGrid()->at(7).end());
}

void BoardIterator::goUp(int num)
{
	if (_currentRowPos + num < getLastRow())
	{
		updateRowPos(std::next(_currentRowPos, num));
	}
	else
	{
		updateRowPos(getLastRow());
	}
}

void BoardIterator::goDown(int num)
{
	if (_currentRowPos - num > getFirstRow())
	{
		updateRowPos(std::prev(_currentRowPos, num));
	}
	else
	{
		updateRowPos(getFirstRow());
	}
}

void BoardIterator::goLeft(int num)
{
	if (_currentColPos - num > getFirstColumn())
	{
		updateColPos(std::prev(_currentColPos, num));
	}
	else
	{
		updateColPos(getFirstColumn());
	}
}

void BoardIterator::goRight(int num)
{
	if (_currentColPos + num < getLastColumn())
	{
		updateColPos(std::next(_currentColPos, num));
	}
	else
	{
		updateColPos(getLastColumn());
	}
}

std::pair<int, int> BoardIterator::getCurrentIndex()
{
	std::pair<int, int> boardIndex;
	boardIndex.first = std::distance(getFirstRow(), _currentRowPos);
	boardIndex.second = std::distance(getFirstColumn(), _currentColPos);

	return boardIndex;
}

void BoardIterator::goToIndex(std::pair<int, int> index)
{
	updatePositions(_board->getBoardGrid()->begin() + index.first, _board->getBoardGrid()->at(0).begin() + index.second);
}

int BoardIterator::getRowSize()
{
	return _board->getBoardGrid()->size();
}

int BoardIterator::getColSize()
{
	return _board->getBoardGrid()->at(0).size();
}

bool BoardIterator::isRowDone()
{
	return _currentRowPos == getLastRow();
}

bool BoardIterator::isColDone()
{
	return _currentColPos == getLastColumn();
}

