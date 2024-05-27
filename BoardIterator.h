#pragma once
#include <iterator>
#include "Chessboard.h"

class BoardIterator
{
	friend class Chessboard;

	private:

		Chessboard* _board;

		std::vector<std::vector<Square>>::iterator _currentRowPos;
		std::vector<std::vector<Square>>::iterator _prevRowPos;

		std::vector<Square>::iterator _currentColPos;
		std::vector<Square>::iterator _prevColPos;

		BoardIterator(Chessboard* board);

		void updatePositions(std::vector<std::vector<Square>>::iterator rowPosition, std::vector<Square>::iterator colPosition);
		void updateRowPos(std::vector<std::vector<Square>>::iterator rowPosition);
		void updateColPos(std::vector<Square>::iterator colPosition);

	public:

		// Returns the iterator's current row position.
		std::vector<std::vector<Square>>::iterator getCurrentRowPos();
		// Returns the iterator's previous row position.
		std::vector<std::vector<Square>>::iterator getPrevRowPos();

		// Returns the iterator's current column position.
		std::vector<Square>::iterator getCurrentColPos();
		// Returns the iterator's previous column position.
		std::vector<Square>::iterator getPrevColPos();

		// Returns an iterator at the first row of the grid (0)
		std::vector<std::vector<Square>>::iterator getFirstRow();
		// Returns an iterator at the last row of the grid (7)
		std::vector<std::vector<Square>>::iterator getLastRow();

		/// <summary>
		/// Gets the first column in the specified row.
		/// </summary>
		/// <param name="row">The row to get the first column of.</param>
		/// <returns>An iterator at the first column in the specified row.</returns>
		std::vector<Square>::iterator getFirstColumn(int row = 0);
		/// <summary>
		/// Gets the last column in the specified row.
		/// </summary>
		/// <param name="row">The row to get the last column of.</param>
		/// <returns>An iterator at the last column in the specified row.</returns>
		std::vector<Square>::iterator getLastColumn(int row = 0);

		// Sends the iterator to the start of the grid (0, 0)
		void goToStart();

		// Sends the iterator to the end of the grid (7,7).
		void goToEnd();

		/// <summary>
		/// Moves the iterator up by the specified number of rows. If it reaches the end of the row, it returns end().
		/// </summary>
		/// <param name="num">The number of rows to move up.</param>
		void goUp(int num = 1);

		void goDown(int num = 1);

		/// <summary>
		/// Moves the iterator left on the board grid, aka decrements columns.
		/// </summary>
		/// <param name="num">The number of columns to move the iterator left.</param>
		void goLeft(int num = 1);

		void goRight(int num = 1);

		// Gets the current board index of the iterators.
		std::pair<int, int> getCurrentIndex();

		// Moves the iterator to the specified board index.
		void goToIndex(std::pair<int, int> index);

		// Gets the size of the iterator's container.
		int getRowSize();
		int getColSize();

		// Returns whether or not the iterator has reached the end of the container.
		bool isRowDone();
		bool isColDone();

	};

