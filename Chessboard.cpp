#include "Chessboard.h"
#include "easylogging++.h"
#include "ServiceLocator.h"
#include "SquareGraphicsComponent.h"
#include <algorithm>

Chessboard::Chessboard() :
	_boardGrid({})
{
	_dimensions = { 0, 0, 1000, 1000 };
	LOG(INFO) << "Chessboard object constructed!";
}

// Copy constructor for deep copy
Chessboard::Chessboard(const Chessboard& board)
{
	_mediator = board._mediator;
	_dimensions = board._dimensions;
	_boardGrid = board._boardGrid;
	LOG(INFO) << "Chessboard deep copy constructor called!";
}


Chessboard::~Chessboard()
{
	LOG(INFO) << "Chessboard destructed!";
}

void Chessboard::initializeBoardGrid()
{
	for (int i = 0; i < 8; ++i)
	{
		std::vector<Square> sqVect{};
		_boardGrid.push_back(sqVect);
	}
}

SDL_Point Chessboard::setBoardDimensionsToWindow()
{
	// Set the position of the chessboard
	int windowW;
	int windowH;
	ServiceLocator::getGraphics().getWindow()->getWindowSize(&windowW, &windowH);
	// Set the board side length to the 2/3rds the size of the minimum dimension of the window size
	int minWindowDimension = (((windowW) < (windowH)) ? (windowW) : (windowH));

	_dimensions.w = (minWindowDimension * 5 / 6);
	_dimensions.h = (minWindowDimension * 5 / 6);

	_dimensions.x = (windowW / 2) - (_dimensions.w / 2);
	_dimensions.y = (windowH / 2) - (_dimensions.h / 2);

	// The point at the bottom left of the board, A1 square
	SDL_Point boardBottomLeft = { _dimensions.x, (_dimensions.y + _dimensions.h) };

	return boardBottomLeft;
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

void Chessboard::setRowTileType(bool odd, std::vector<Square>& sqVect)
{
	int i = odd;
	for (i; i < sqVect.size(); i += 2)
	{
		sqVect[i].setTileType(Square::LIGHT);
	}
}

Square Chessboard::createSquare(const std::string& name)
{
	Square square{ name };
	square.setScale(_dimensions.w / 8, _dimensions.h / 8);
	square.getGraphicsComponent()->loadTexture(square);
	square.getGraphicsComponent()->sumImage(&square);
	return square;
}

void const Chessboard::buildChessboard()
{

	SDL_Point boardBottomLeft = setBoardDimensionsToWindow();

	std::vector<std::string> sqN{ 
		"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
		"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
		"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
		"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
		"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
		"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
		"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
		"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
	};

	auto nameItr = sqN.begin();
	bool odd = true;
	
	for (int row = 0; row < 8; ++row)
	{
		_boardGrid.push_back(std::vector<Square>{});
		for (int col = 0; col < 8; ++col)
		{
			_boardGrid.at(row).push_back(createSquare(*(nameItr)));
			++nameItr;
		}

		((row + 1) % 2 == 0) ? odd = false : odd = true;
		setRowTileType(odd, _boardGrid[row]);
		setRowSquarePosition(boardBottomLeft, _boardGrid[row], row + 1);
	}

	// Set the board index for every square in the board
	for (int row = 0; row < _boardGrid.size(); ++row)
	{
		for (int column = 0; column < _boardGrid[row].size(); ++column)
		{
			_boardGrid.at(row).at(column).setBoardIndex(row, column);
		}
	}

}

void const Chessboard::addBoardToRender()
{
	std::vector<IDrawable*> renderVect;

	for (int row = 0; row < _boardGrid.size(); ++row)
	{
		for (int column = 0; column < _boardGrid[row].size(); ++column)
			renderVect.push_back(_boardGrid[row][column].getGraphicsComponent());
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
			LOG(DEBUG) << "[ " << _boardGrid[row][column].getName() << " Index: [ " << _boardGrid[row][column].getBoardIndex().first << ", " << _boardGrid[row][column].getBoardIndex().second << " ] " << " ]\nX: " << _boardGrid[row][column].getX() << "\nY: " << _boardGrid[row][column].getY() << "\nZ: " << _boardGrid[row][column].getGraphicsComponent()->getZ() << "\nW: " << _boardGrid[row][column].getWidth() << "\nH: " << _boardGrid[row][column].getHeight();
		}
	}
}

std::shared_ptr<Square> Chessboard::getSquareByName(const std::string& name)
{
	std::vector<Square>::iterator itr;

	for (int row = 0; row < _boardGrid.size(); ++row)
	{
		for (int col = 0; col < _boardGrid.at(row).size(); ++col)
		{
			if (_boardGrid.at(row).at(col).getName() == name)
			{
				return std::make_shared<Square>(_boardGrid.at(row).at(col));
			}
		}
	}

	return nullptr;
}