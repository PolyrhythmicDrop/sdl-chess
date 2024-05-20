#include "Chessboard.h"
#include "easylogging++.h"
#include "ServiceLocator.h"
#include "SquareGraphicsComponent.h"
#include <algorithm>

Chessboard::Chessboard() :
	_graphics(new GraphicsComponent())
{
	_dimensions = { 0, 0, 1000, 1000 };
	_zIndex = -1;
	LOG(INFO) << "Chessboard object constructed!";
}

// Copy constructor for deep copy
Chessboard::Chessboard(const Chessboard& board)
{
	_graphics = new GraphicsComponent();
	*_graphics = *(board._graphics);
	_dimensions = board._dimensions;
	_zIndex = board._zIndex;
	_boardGrid = board._boardGrid;
	LOG(INFO) << "Chessboard deep copy constructor called!";
}


Chessboard::~Chessboard()
{
	LOG(INFO) << "Chessboard destructed!";
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
	//
	int squareSideSize = _dimensions.h / 8;

	// *** //
	// Create the first row of squares
	Square a1("a1", this);
	Square b1("b1", this);
	Square c1("c1", this);
	Square d1("d1", this);
	Square e1("e1", this);
	Square f1("f1", this);
	Square g1("g1", this);
	Square h1("h1", this);

	// Set the size of each square
	std::vector<Square> row1Vect = { a1, b1, c1, d1, e1, f1, g1, h1 };
	LOG(TRACE) << "Squares added to Row 1 Vector!";
	

	/*
	// Set the square's index in the board vector
	for (int i = 0; i < row1Vect.size(); ++i)
	{
		row1Vect.at(i).setBoardIndex(0, i);
		LOG(DEBUG) << row1Vect.at(i).getName() << " board index: " << row1Vect.at(i).getBoardIndex().first << ", " << row1Vect.at(i).getBoardIndex().second;
	}
	*/

	for (Square square : row1Vect)
	{
		square.setScale(squareSideSize, squareSideSize);
		square._draw = true;
	}

	// Alternate the tile type, depending on the row
	for (int i = 1; i < row1Vect.size(); ++i)
	{
		row1Vect[i].setTileType(Square::LIGHT);
		++i;
	}
	
	// Set the positions for the first row of squares
	row1Vect[0].setPosition(boardBottomLeft.x, boardBottomLeft.y - row1Vect[0].getHeight());
	row1Vect[1].setPosition(boardBottomLeft.x + row1Vect[0].getWidth(), row1Vect[0].getY());
	for (int i = 2; i < row1Vect.size(); ++i)
	{
		row1Vect[i].setPosition(row1Vect[i -1].getX() + row1Vect[i - 1].getWidth(), row1Vect[i - 1].getY());
	}
	// *** //

	// *** //
	// Create the second row of squares
	Square a2("a2", this);
	Square b2("b2", this);
	Square c2("c2", this);
	Square d2("d2", this);
	Square e2("e2", this);
	Square f2("f2", this);
	Square g2("g2", this);
	Square h2("h2", this);

	// Set the size of each square
	std::vector<Square> row2Vect = { a2, b2, c2, d2, e2, f2, g2, h2 };
	LOG(TRACE) << "Squares added to Row 2 Vector!";

	// Alternate the tile type, depending on the row
	for (int i = 0; i < row2Vect.size(); ++i)
	{
		row2Vect[i].setTileType(Square::LIGHT);
		++i;
	}

	for (Square square : row2Vect)
	{
		square.setScale(squareSideSize, squareSideSize);
		square._draw = true;
	}

	// Set the positions for the first row of squares
	row2Vect[0].setPosition(boardBottomLeft.x, boardBottomLeft.y - (row2Vect[0].getHeight() * 2));
	row2Vect[1].setPosition(boardBottomLeft.x + row2Vect[0].getWidth(), row2Vect[0].getY());
	for (int i = 2; i < row2Vect.size(); ++i)
	{
		row2Vect[i].setPosition(row2Vect[i - 1].getX() + row2Vect[i - 1].getWidth(), row2Vect[i - 1].getY());
	}
	// *** //

	// *** //
	// Create the third row of squares
	Square a3("a3", this);
	Square b3("b3", this);
	Square c3("c3", this);
	Square d3("d3", this);
	Square e3("e3", this);
	Square f3("f3", this);
	Square g3("g3", this);
	Square h3("h3", this);

	// Set the size of each square
	std::vector<Square> row3Vect = { a3, b3, c3, d3, e3, f3, g3, h3 };
	LOG(TRACE) << "Squares added to Row 3 Vector!";


	// Alternate the tile type, depending on the row
	for (int i = 1; i < row3Vect.size(); i += 2)
	{
		row3Vect[i].setTileType(Square::LIGHT);
	}

	for (Square square : row3Vect)
	{
		square.setScale(squareSideSize, squareSideSize);
		square._draw = true;
	}

	// Set the positions for the first row of squares
	row3Vect[0].setPosition(boardBottomLeft.x, boardBottomLeft.y - (row3Vect[0].getHeight() * 3));
	row3Vect[1].setPosition(boardBottomLeft.x + row3Vect[0].getWidth(), row3Vect[0].getY());
	for (int i = 2; i < row3Vect.size(); ++i)
	{
		row3Vect[i].setPosition(row3Vect[i - 1].getX() + row3Vect[i - 1].getWidth(), row3Vect[i - 1].getY());
	}
	// *** //

	// *** //
	// Create the fourth row of squares
	Square a4("a4", this);
	Square b4("b4", this);
	Square c4("c4", this);
	Square d4("d4", this);
	Square e4("e4", this);
	Square f4("f4", this);
	Square g4("g4", this);
	Square h4("h4", this);

	// Set the size of each square
	std::vector<Square> row4Vect = { a4, b4, c4, d4, e4, f4, g4, h4 };
	LOG(TRACE) << "Squares added to Row 4 Vector!";

	for (int i = 0; i < row4Vect.size(); ++i)
	{
		row4Vect[i].setTileType(Square::LIGHT);
		i++;
	}

	for (Square square : row4Vect)
	{
		square.setScale(squareSideSize, squareSideSize);
		square._draw = true;
	}


	// Set the positions for the fourth row of squares
	row4Vect[0].setPosition(boardBottomLeft.x, boardBottomLeft.y - (row4Vect[0].getHeight() * 4));
	row4Vect[1].setPosition(boardBottomLeft.x + row4Vect[0].getWidth(), row4Vect[0].getY());
	for (int i = 2; i < row4Vect.size(); ++i)
	{
		row4Vect[i].setPosition(row4Vect[i - 1].getX() + row4Vect[i - 1].getWidth(), row4Vect[i - 1].getY());
	}
	// *** //

	// *** //
	// Create the fifth row of squares
	Square a5("a5", this);
	Square b5("b5", this);
	Square c5("c5", this);
	Square d5("d5", this);
	Square e5("e5", this);
	Square f5("f5", this);
	Square g5("g5", this);
	Square h5("h5", this);

	// Set the size of each square
	std::vector<Square> row5Vect = { a5, b5, c5, d5, e5, f5, g5, h5 };
	LOG(TRACE) << "Squares added to Row 5 Vector!";

	// Alternate the tile type, depending on the row
	for (int i = 1; i < row5Vect.size(); ++i)
	{
		row5Vect[i].setTileType(Square::LIGHT);
		++i;
	}

	for (Square square : row5Vect)
	{
		square.setScale(squareSideSize, squareSideSize);
		square._draw = true;
	}


	// Set the positions for the first row of squares
	row5Vect[0].setPosition(boardBottomLeft.x, boardBottomLeft.y - (row5Vect[0].getHeight() * 5));
	row5Vect[1].setPosition(boardBottomLeft.x + row5Vect[0].getWidth(), row5Vect[0].getY());
	for (int i = 2; i < row5Vect.size(); ++i)
	{
		row5Vect[i].setPosition(row5Vect[i - 1].getX() + row5Vect[i - 1].getWidth(), row5Vect[i - 1].getY());
	}
	// *** //

	// *** //
	// Create the sixth row of squares
	Square a6("a6", this);
	Square b6("b6", this);
	Square c6("c6", this);
	Square d6("d6", this);
	Square e6("e6", this);
	Square f6("f6", this);
	Square g6("g6", this);
	Square h6("h6", this);

	// Set the size of each square
	std::vector<Square> row6Vect = { a6, b6, c6, d6, e6, f6, g6, h6 };
	LOG(TRACE) << "Squares added to Row 6 Vector!";

	// Alternate the tile type, depending on the row
	for (int i = 0; i < row6Vect.size(); ++i)
	{
		row6Vect[i].setTileType(Square::LIGHT);
		++i;
	}

	for (Square square : row6Vect)
	{
		square.setScale(squareSideSize, squareSideSize);
		square._draw = true;		
	}

	// Set the positions for the first row of squares
	row6Vect[0].setPosition(boardBottomLeft.x, boardBottomLeft.y - (row6Vect[0].getHeight() * 6));
	row6Vect[1].setPosition(boardBottomLeft.x + row6Vect[0].getWidth(), row6Vect[0].getY());
	for (int i = 2; i < row6Vect.size(); ++i)
	{
		row6Vect[i].setPosition(row6Vect[i - 1].getX() + row6Vect[i - 1].getWidth(), row6Vect[i - 1].getY());
	}
	// *** //

	// *** //
	// Create the seventh row of squares
	Square a7("a7", this);
	Square b7("b7", this);
	Square c7("c7", this);
	Square d7("d7", this);
	Square e7("e7", this);
	Square f7("f7", this);
	Square g7("g7", this);
	Square h7("h7", this);

	// Set the size of each square
	std::vector<Square> row7Vect = { a7, b7, c7, d7, e7, f7, g7, h7 };
	LOG(TRACE) << "Squares added to Row 7 Vector!";

	// Alternate the tile type, depending on the row
	for (int i = 1; i < row7Vect.size(); ++i)
	{
		row7Vect[i].setTileType(Square::LIGHT);
		++i;
	}

	for (Square square : row7Vect)
	{
		square.setScale(squareSideSize, squareSideSize);
		square._draw = true;
		
	}

	// Set the positions for the first row of squares
	row7Vect[0].setPosition(boardBottomLeft.x, boardBottomLeft.y - (row7Vect[0].getHeight() * 7));
	row7Vect[1].setPosition(boardBottomLeft.x + row7Vect[0].getWidth(), row7Vect[0].getY());
	for (int i = 2; i < row7Vect.size(); ++i)
	{
		row7Vect[i].setPosition(row7Vect[i - 1].getX() + row7Vect[i - 1].getWidth(), row7Vect[i - 1].getY());
	}
	// *** //

	// *** //
	// Create the eigth row of squares
	Square a8("a8", this);
	Square b8("b8", this);
	Square c8("c8", this);
	Square d8("d8", this);
	Square e8("e8", this);
	Square f8("f8", this);
	Square g8("g8", this);
	Square h8("h8", this);

	// Set the size of each square
	std::vector<Square> row8Vect = { a8, b8, c8, d8, e8, f8, g8, h8 };
	LOG(INFO) << "Squares added to Row 8 Vector!";

	// Alternate the tile type, depending on the row
	for (int i = 0; i < row8Vect.size(); ++i)
	{
		row8Vect[i].setTileType(Square::LIGHT);
		++i;
	}

	for (Square square : row8Vect)
	{
		square.setScale(squareSideSize, squareSideSize);
		square._draw = true;
	}

	// Set the positions for the first row of squares
	row8Vect[0].setPosition(boardBottomLeft.x, boardBottomLeft.y - (row8Vect[0].getHeight() * 8));
	row8Vect[1].setPosition(boardBottomLeft.x + row8Vect[0].getWidth(), row8Vect[0].getY());
	for (int i = 2; i < row8Vect.size(); ++i)
	{
		row8Vect[i].setPosition(row8Vect[i - 1].getX() + row8Vect[i - 1].getWidth(), row8Vect[i - 1].getY());
	}
	// *** //
	
	// Add the row vectors to the board grid vector
	this->_boardGrid.push_back(row1Vect);
	this->_boardGrid.push_back(row2Vect);
	this->_boardGrid.push_back(row3Vect);
	this->_boardGrid.push_back(row4Vect);
	this->_boardGrid.push_back(row5Vect);
	this->_boardGrid.push_back(row6Vect);
	this->_boardGrid.push_back(row7Vect);
	this->_boardGrid.push_back(row8Vect);

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
			renderVect.push_back(std::pair<GameObject*, SDL_Texture*>(&_boardGrid[row][column], _boardGrid[row][column].getGraphicsComponent()->getSdlTexture()));
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
