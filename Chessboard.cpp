#include "Chessboard.h"
#include "easylogging++.h"
#include "ServiceLocator.h"
#include "SquareGraphicsComponent.h"
#include <algorithm>

Chessboard::Chessboard()
{
	_dimensions = { 0, 0, 1000, 1000 };
	_zIndex = -1;
	LOG(INFO) << "Chessboard object constructed!";
}

// Copy constructor for deep copy
Chessboard::Chessboard(const Chessboard& board)
{
	_mediator = board._mediator;
	_dimensions = board._dimensions;
	_zIndex = board._zIndex;
	_boardGrid = board._boardGrid;
	LOG(INFO) << "Chessboard deep copy constructor called!";
}


Chessboard::~Chessboard()
{
	LOG(INFO) << "Chessboard destructed!";
}

Square Chessboard::createSquare(std::string name)
{
	Square square{ name };
	square.setScale(_dimensions.w / 8, _dimensions.h / 8);
	return square;
}

void Chessboard::setRowSquarePosition(SDL_Point origin, std::vector<Square>& sqVect, int rowNum)
{
	sqVect[0].setPosition(origin.x, origin.y - (sqVect[0].getHeight() * rowNum));
	sqVect[1].setPosition(origin.x + sqVect[0].getWidth(), sqVect[0].getY());
	for (int i = 2; i < sqVect.size(); ++i)
	{
		sqVect[i].setPosition(sqVect[i - 1].getX() + sqVect[i - 1].getWidth(), sqVect[i - 1].getY());
	}
}

void const Chessboard::buildChessboard()
{
	// Set the position of the chessboard
	int windowW;
	int windowH;
	ServiceLocator::getGraphics().getWindow()->getWindowSize(&windowW, &windowH);
	// Set the board side length to the 2/3rds the size of the minimum dimension of the window size
	int minWindowDimension = (((windowW) < (windowH)) ? (windowW) : (windowH));

	_dimensions.w = (minWindowDimension * 5/6);
	_dimensions.h = (minWindowDimension * 5/6);

	_dimensions.x = (windowW / 2) - (_dimensions.w / 2);
	_dimensions.y = (windowH / 2) - (_dimensions.h / 2);

	// The point at the bottom left of the board, A1 square
	SDL_Point boardBottomLeft = { _dimensions.x, (_dimensions.y + _dimensions.h) };

	// *** //
	// Create the first row of squares

	std::vector<std::string> sqNames{ "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1" };
	std::vector<Square> row1Vect{};

	for (int i = 0; i < sqNames.size(); ++i)
	{
		row1Vect.push_back(createSquare(sqNames[i]));
	}

	LOG(TRACE) << "Squares added to Row 1 Vector!";

	// Alternate the tile type, depending on the row
	for (int i = 1; i < row1Vect.size(); ++i)
	{
		row1Vect[i].setTileType(Square::LIGHT);
		++i;
	}

	setRowSquarePosition(boardBottomLeft, row1Vect, 1);

	sqNames.clear();
	// *** //

	// *** //
	// Create the second row of squares

	sqNames = { "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2" };
	std::vector<Square> row2Vect{};

	for (int i = 0; i < sqNames.size(); ++i)
	{
		row2Vect.push_back(createSquare(sqNames[i]));
	}

	LOG(TRACE) << "Squares added to Row 2 Vector!";

	// Alternate the tile type, depending on the row
	for (int i = 0; i < row2Vect.size(); ++i)
	{
		row2Vect[i].setTileType(Square::LIGHT);
		++i;
	}

	setRowSquarePosition(boardBottomLeft, row2Vect, 2);

	sqNames.clear();
	// *** //

	// *** //
	// Create the third row of squares
	sqNames = { "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3" };
	std::vector<Square> row3Vect{};

	for (int i = 0; i < sqNames.size(); ++i)
	{
		row3Vect.push_back(createSquare(sqNames[i]));
	}

	LOG(TRACE) << "Squares added to Row 3 Vector!";

	// Alternate the tile type, depending on the row
	for (int i = 1; i < row3Vect.size(); i += 2)
	{
		row3Vect[i].setTileType(Square::LIGHT);
	}

	setRowSquarePosition(boardBottomLeft, row3Vect, 3);

	sqNames.clear();
	// *** //

	// *** //
	// Create the fourth row of squares
	sqNames = { "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4" };
	std::vector<Square> row4Vect{};

	for (int i = 0; i < sqNames.size(); ++i)
	{
		row4Vect.push_back(createSquare(sqNames[i]));
	}

	LOG(TRACE) << "Squares added to Row 4 Vector!";

	// Alternate the tile type, depending on the row
	for (int i = 0; i < row4Vect.size(); ++i)
	{
		row4Vect[i].setTileType(Square::LIGHT);
		++i;
	}

	setRowSquarePosition(boardBottomLeft, row4Vect, 4);

	sqNames.clear();
	// *** //

	// *** //
	// Create the fifth row of squares
	sqNames = { "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5" };
	std::vector<Square> row5Vect{};

	for (int i = 0; i < sqNames.size(); ++i)
	{
		row5Vect.push_back(createSquare(sqNames[i]));
	}

	LOG(TRACE) << "Squares added to Row 5 Vector!";

	// Alternate the tile type, depending on the row
	for (int i = 1; i < row5Vect.size(); i += 2)
	{
		row5Vect[i].setTileType(Square::LIGHT);
	}

	setRowSquarePosition(boardBottomLeft, row5Vect, 5);

	sqNames.clear();
	// *** //

	// *** //
	// Create the sixth row of squares
	sqNames = { "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6" };
	std::vector<Square> row6Vect{};

	for (int i = 0; i < sqNames.size(); ++i)
	{
		row6Vect.push_back(createSquare(sqNames[i]));
	}

	LOG(TRACE) << "Squares added to Row 6 Vector!";

	// Alternate the tile type, depending on the row
	for (int i = 0; i < row6Vect.size(); ++i)
	{
		row6Vect[i].setTileType(Square::LIGHT);
		++i;
	}

	setRowSquarePosition(boardBottomLeft, row6Vect, 6);

	sqNames.clear();
	// *** //

	// *** //
	// Create the seventh row of squares
	sqNames = { "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7" };
	std::vector<Square> row7Vect{};

	for (int i = 0; i < sqNames.size(); ++i)
	{
		row7Vect.push_back(createSquare(sqNames[i]));
	}

	LOG(TRACE) << "Squares added to Row 7 Vector!";

	// Alternate the tile type, depending on the row
	for (int i = 1; i < row7Vect.size(); i += 2)
	{
		row7Vect[i].setTileType(Square::LIGHT);
	}

	setRowSquarePosition(boardBottomLeft, row7Vect, 7);

	sqNames.clear();
	// *** //

	// *** //
	// Create the eigth row of squares
	sqNames = { "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8" };
	std::vector<Square> row8Vect{};

	for (int i = 0; i < sqNames.size(); ++i)
	{
		row8Vect.push_back(createSquare(sqNames[i]));
	}

	LOG(TRACE) << "Squares added to Row 8 Vector!";

	// Alternate the tile type, depending on the row
	for (int i = 0; i < row8Vect.size(); ++i)
	{
		row8Vect[i].setTileType(Square::LIGHT);
		++i;
	}

	setRowSquarePosition(boardBottomLeft, row8Vect, 8);

	sqNames.clear();
	// *** //
	
	// Add the row vectors to the board grid vector
	_boardGrid.push_back(row1Vect);
	_boardGrid.push_back(row2Vect);
	_boardGrid.push_back(row3Vect);
	_boardGrid.push_back(row4Vect);
	_boardGrid.push_back(row5Vect);
	_boardGrid.push_back(row6Vect);
	_boardGrid.push_back(row7Vect);
	_boardGrid.push_back(row8Vect);

	// Set the board index for every square in the board
	for (int row = 0; row < _boardGrid.size(); ++row)
	{
		for (int column = 0; column < _boardGrid[row].size(); ++column)
		{
			_boardGrid[row][column].setBoardIndex(row, column);
		}
	}

}

void const Chessboard::addBoardToRender()
{
	std::vector<std::pair<GameObject*, SDL_Texture*>> renderVect;

	for (int row = 0; row < _boardGrid.size(); ++row)
	{
		for (int column = 0; column < _boardGrid[row].size(); ++column)
			renderVect.push_back(std::pair<GameObject*, SDL_Texture*>(&_boardGrid[row][column], _boardGrid[row][column].getGraphicsComponent()->getCurrentTexture()));
	}

	ServiceLocator::getGraphics().addToRenderMap(1, renderVect);
}

void const Chessboard::printSquarePositions()
{
	LOG(DEBUG) << "The size of the board grid is: " << _boardGrid.size() << " rows and " << _boardGrid[0].size() << " columns.";

	// Debug: get the coordinates for each item in the grid and put them in the log
	for (int row = 0; row < _boardGrid.size(); ++row)
	{
		LOG(DEBUG) << "";
		for (int column = 0; column < _boardGrid[row].size(); ++column)
		{
			LOG(DEBUG) << "[ " << _boardGrid[row][column].getName() << " Index: [ " << _boardGrid[row][column].getBoardIndex().first << ", " << _boardGrid[row][column].getBoardIndex().second << " ] " << " ]\nX: " << _boardGrid[row][column].getX() << "\nY: " << _boardGrid[row][column].getY() << "\nZ: " << _boardGrid[row][column].getZ() << "\nW: " << _boardGrid[row][column].getWidth() << "\nH: " << _boardGrid[row][column].getHeight();
		}
	}
}

Square* Chessboard::getSquareByName(std::string name)
{
	std::vector<Square>::iterator itr;

	for (int row = 0; row < _boardGrid.size(); ++row)
	{
		for (int col = 0; col < _boardGrid.at(row).size(); ++col)
		{
			if (_boardGrid.at(row).at(col).getName() == name)
			{
				return &_boardGrid.at(row).at(col);
			}
		}
	}

	return nullptr;
}