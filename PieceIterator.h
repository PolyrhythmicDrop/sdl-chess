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

	// Returns the iterator's current position within the container.
	std::vector<Piece>::iterator getCurrentPosition();
	// Returns the iterator's previous position within the container.
	std::vector<Piece>::iterator getPreviousPosition();

	// Returns an iterator at the start of the container
	std::vector<Piece>::iterator getContainerBegin();
	// Returns an iterator at the end of the container.
	std::vector<Piece>::iterator getContainerEnd();

	// Sends the iterator to the start of the container
	void goToStart();
	/// <summary>
	/// Moves the iterator forward in the container
	/// </summary>
	/// <param name="num">The number of entries to move the iterator forward.</param>
	void goForward(int num);
	/// <summary>
	/// Moves the iterator backward in the container.
	/// </summary>
	/// <param name="num">The number of entries to move the iterator backward.</param>
	void goBack(int num);
	// Moves the iterator to the end of the container.
	void goToEnd();

	// Gets the index value of the iterator's current position, aka the iterator's distance from the beginning of the container.
	int getIndex();
	// Moves the iterator to the specified index in the container.
	void goToIndex(int index);

	// Gets the size of the iterator's container.
	int getSize();
	// Returns whether or not the iterator has reached the end of the container.
	bool isDone();

};

