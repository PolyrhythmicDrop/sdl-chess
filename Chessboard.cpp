#include "Chessboard.h"
#include "easylogging++.h"
#include "ServiceLocator.h"

Chessboard::Chessboard(BoardSkin skin) :
	_graphics(new GraphicsComponent()),
	_skin(skin)
{
	switch(_skin)
	{case STANDARD:
		_graphics->setImgPath("images/chessboard-compressed.png");
		break;
	}
	_graphics->loadTexture();
	int w, h;
	SDL_QueryTexture(_graphics->getSdlTexture(), NULL, NULL, &w, &h);
	setScaleFromTexture(_graphics->getSdlTexture());
	_zIndex = 1;
	LOG(INFO) << "Chessboard constructed!";
}

// Copy constructor for deep copy
Chessboard::Chessboard(const Chessboard& board)
{
	_skin = board._skin;
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
	_dimensions.x = (windowW / 2) - (_dimensions.w / 2);
	_dimensions.y = (windowH / 2) - (_dimensions.h / 2);

	// The point at the bottom left of the board, A1 square
	SDL_Point boardBottomLeft = { _dimensions.x, (_dimensions.y + _dimensions.h) };
	//
	int squareSideSize = _dimensions.w / 8;

	// Number of rows and columns in board grid
	int num_col = 8;
	int num_row = 8;

	// *** //
	// Create the first row of squares
	Square a1("a1");
	Square b1("b1");
	Square c1("c1");
	Square d1("d1");
	Square e1("e1");
	Square f1("f1");
	Square g1("g1");
	Square h1("h1");

	// Set the size of each square
	std::vector<Square> row1Vect = { a1, b1, c1, d1, e1, f1, g1, h1 };
	LOG(INFO) << "Squares added to Row 1 Vector!";
	for (Square square : row1Vect)
	{
		square.setScale(squareSideSize, squareSideSize);
		square.setOverlayType(Square::MOVE);
		square._draw = true;
		for (int i = 0; i < row1Vect.size(); ++i)
		{
			row1Vect[i].setZ(2 + i);
		}
	}
	LOG(INFO) << "Scale and overlay of squares in Row 1 vector set!";

	std::vector<Square>::iterator itr;
	itr = row1Vect.begin();
	itr = itr + 2;
	// Set the positions for the first row of squares
	row1Vect[0].setPosition(boardBottomLeft.x, boardBottomLeft.y - row1Vect[0].getWidth());
	row1Vect[1].setPosition(boardBottomLeft.x + row1Vect[0].getWidth(), row1Vect[0].getY());
	for (int i = 2; i < row1Vect.size(); ++i)
	{
		row1Vect[i].setPosition(row1Vect[i -1].getX() + row1Vect[i - 1].getWidth(), row1Vect[i - 1].getY());
	}
	// *** //

	// *** //
	// Create the second row of squares
	Square a2("a2");
	Square b2("b2");
	Square c2("c2");
	Square d2("d2");
	Square e2("e2");
	Square f2("f2");
	Square g2("g2");
	Square h2("h2");

	// Set the size of each square
	std::vector<Square> row2Vect = { a2, b2, c2, d2, e2, f2, g2, h2 };
	LOG(INFO) << "Squares added to Row 2 Vector!";
	for (Square square : row2Vect)
	{
		square.setScale(squareSideSize, squareSideSize);
		square.setOverlayType(Square::MOVE);
		square._draw = true;
		for (int i = 0; i < row2Vect.size(); ++i)
		{
			// Set the Z value for each square. Don't forget to increase this by 8 for each row of squares, so every Z-value is unique.
			row2Vect[i].setZ(10 + i);
		}
	}
	LOG(INFO) << "Scale and overlay of squares in Row 1 vector set!";

	itr = row2Vect.begin();
	itr = itr + 2;
	// Set the positions for the first row of squares
	row2Vect[0].setPosition(boardBottomLeft.x, boardBottomLeft.y - (row2Vect[0].getWidth() * 2));
	row2Vect[1].setPosition(boardBottomLeft.x + row2Vect[0].getWidth(), row2Vect[0].getY());
	for (int i = 2; i < row2Vect.size(); ++i)
	{
		row2Vect[i].setPosition(row2Vect[i - 1].getX() + row2Vect[i - 1].getWidth(), row2Vect[i - 1].getY());
	}


	
	
	// Add the row vectors to the board grid vector
	this->_boardGrid.push_back(row2Vect);
	this->_boardGrid.push_back(row1Vect);


}
