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
	
	for (int i = 1; i < row1Vect.size(); ++i)
	{
		row1Vect[i].setTileType(Square::LIGHT);
		++i;
	}
	

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
	LOG(INFO) << "Scale and overlay of squares in Row 2 vector set!";

	itr = row2Vect.begin();
	itr = itr + 2;
	// Set the positions for the first row of squares
	row2Vect[0].setPosition(boardBottomLeft.x, boardBottomLeft.y - (row2Vect[0].getWidth() * 2));
	row2Vect[1].setPosition(boardBottomLeft.x + row2Vect[0].getWidth(), row2Vect[0].getY());
	for (int i = 2; i < row2Vect.size(); ++i)
	{
		row2Vect[i].setPosition(row2Vect[i - 1].getX() + row2Vect[i - 1].getWidth(), row2Vect[i - 1].getY());
	}
	// *** //

	// *** //
	// Create the third row of squares
	Square a3("a3");
	Square b3("b3");
	Square c3("c3");
	Square d3("d3");
	Square e3("e3");
	Square f3("f3");
	Square g3("g3");
	Square h3("h3");

	// Set the size of each square
	std::vector<Square> row3Vect = { a3, b3, c3, d3, e3, f3, g3, h3 };
	LOG(INFO) << "Squares added to Row 2 Vector!";
	for (Square square : row3Vect)
	{
		square.setScale(squareSideSize, squareSideSize);
		square.setOverlayType(Square::MOVE);
		square._draw = true;
		for (int i = 0; i < row3Vect.size(); ++i)
		{
			// Set the Z value for each square. Don't forget to increase this by 8 for each row of squares, so every Z-value is unique.
			row3Vect[i].setZ(18 + i);
		}
	}
	LOG(INFO) << "Scale and overlay of squares in Row 3 vector set!";

	itr = row3Vect.begin();
	itr = itr + 2;
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
	Square a4("a4");
	Square b4("b4");
	Square c4("c4");
	Square d4("d4");
	Square e4("e4");
	Square f4("f4");
	Square g4("g4");
	Square h4("h4");

	// Set the size of each square
	std::vector<Square> row4Vect = { a4, b4, c4, d4, e4, f4, g4, h4 };
	LOG(INFO) << "Squares added to Row 4 Vector!";
	for (Square square : row4Vect)
	{
		square.setScale(squareSideSize, squareSideSize);
		square.setOverlayType(Square::MOVE);
		square._draw = true;
		for (int i = 0; i < row4Vect.size(); ++i)
		{
			// Set the Z value for each square. Don't forget to increase this by 8 for each row of squares, so every Z-value is unique.
			row4Vect[i].setZ(26 + i);
		}
	}
	LOG(INFO) << "Scale and overlay of squares in Row 3 vector set!";

	itr = row4Vect.begin();
	itr = itr + 2;
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
	Square a5("a5");
	Square b5("b5");
	Square c5("c5");
	Square d5("d5");
	Square e5("e5");
	Square f5("f5");
	Square g5("g5");
	Square h5("h5");

	// Set the size of each square
	std::vector<Square> row5Vect = { a5, b5, c5, d5, e5, f5, g5, h5 };
	LOG(INFO) << "Squares added to Row 5 Vector!";
	for (Square square : row5Vect)
	{
		square.setScale(squareSideSize, squareSideSize);
		square.setOverlayType(Square::MOVE);
		square._draw = true;
		for (int i = 0; i < row5Vect.size(); ++i)
		{
			// Set the Z value for each square. Don't forget to increase this by 8 for each row of squares, so every Z-value is unique.
			row5Vect[i].setZ(34 + i);
		}
	}
	LOG(INFO) << "Scale and overlay of squares in Row 3 vector set!";

	itr = row5Vect.begin();
	itr = itr + 2;
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
	Square a6("a6");
	Square b6("b6");
	Square c6("c6");
	Square d6("d6");
	Square e6("e6");
	Square f6("f6");
	Square g6("g6");
	Square h6("h6");

	// Set the size of each square
	std::vector<Square> row6Vect = { a6, b6, c6, d6, e6, f6, g6, h6 };
	LOG(INFO) << "Squares added to Row 6 Vector!";
	for (Square square : row6Vect)
	{
		square.setScale(squareSideSize, squareSideSize);
		square.setOverlayType(Square::MOVE);
		square._draw = true;
		for (int i = 0; i < row6Vect.size(); ++i)
		{
			// Set the Z value for each square. Don't forget to increase this by 8 for each row of squares, so every Z-value is unique.
			row6Vect[i].setZ(42 + i);
		}
	}
	LOG(INFO) << "Scale and overlay of squares in Row 6 vector set!";

	itr = row6Vect.begin();
	itr = itr + 2;
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
	Square a7("a7");
	Square b7("b7");
	Square c7("c7");
	Square d7("d7");
	Square e7("e7");
	Square f7("f7");
	Square g7("g7");
	Square h7("h7");

	// Set the size of each square
	std::vector<Square> row7Vect = { a7, b7, c7, d7, e7, f7, g7, h7 };
	LOG(INFO) << "Squares added to Row 6 Vector!";
	for (Square square : row7Vect)
	{
		square.setScale(squareSideSize, squareSideSize);
		square.setOverlayType(Square::MOVE);
		square._draw = true;
		for (int i = 0; i < row7Vect.size(); ++i)
		{
			// Set the Z value for each square. Don't forget to increase this by 8 for each row of squares, so every Z-value is unique.
			row7Vect[i].setZ(50 + i);
		}
	}
	LOG(INFO) << "Scale and overlay of squares in Row 7 vector set!";

	itr = row7Vect.begin();
	itr = itr + 2;
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
	Square a8("a8");
	Square b8("b8");
	Square c8("c8");
	Square d8("d8");
	Square e8("e8");
	Square f8("f8");
	Square g8("g8");
	Square h8("h8");

	// Set the size of each square
	std::vector<Square> row8Vect = { a8, b8, c8, d8, e8, f8, g8, h8 };
	LOG(INFO) << "Squares added to Row 8 Vector!";
	for (Square square : row8Vect)
	{
		square.setScale(squareSideSize, squareSideSize);
		square.setOverlayType(Square::MOVE);
		square._draw = true;
		for (int i = 0; i < row8Vect.size(); ++i)
		{
			// Set the Z value for each square. Don't forget to increase this by 8 for each row of squares, so every Z-value is unique.
			row8Vect[i].setZ(58 + i);
		}
	}
	LOG(INFO) << "Scale and overlay of squares in Row 6 vector set!";

	itr = row8Vect.begin();
	itr = itr + 2;
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
}
