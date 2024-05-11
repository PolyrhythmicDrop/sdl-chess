#include "Chessboard.h"
#include "easylogging++.h"
#include "ServiceLocator.h"

Chessboard::Chessboard(BoardSkin skin) :
	_graphics(new GraphicsComponent()),
	_skin(skin),
	_boardDimensions({ 0, 0, 0, 0 })
{
	switch(_skin)
	{case STANDARD:
		_graphics->setImgPath("images/chessboard-compressed.png");
		break;
	}
	_graphics->loadTexture();
	int w, h;
	SDL_QueryTexture(_graphics->getSdlTexture(), NULL, NULL, &w, &h);
	_boardDimensions.w = w;
	_boardDimensions.h = h;	
	LOG(INFO) << "Chessboard constructed!";
}

Chessboard::~Chessboard()
{
	LOG(INFO) << "Chessboard destructed!";
}

void Chessboard::buildChessboard()
{
	// Set the position of the chessboard
	int windowW;
	int windowH;
	ServiceLocator::getGraphics().getWindow()->getWindowSize(&windowW, &windowH);
	_boardDimensions.x = (windowW / 2) - (_boardDimensions.w / 2);
	_boardDimensions.y = (windowH / 2) - (_boardDimensions.h / 2);

	SDL_Point boardBottomLeft = { _boardDimensions.x, (_boardDimensions.y - _boardDimensions.h) };

	int squareSideSize = _boardDimensions.w / 8;

	// Number of rows and columns in board grid
	int num_col = 8;
	int num_row = 8;

	// Create the map of strings and rects for the first row (for now, just try to get them positioned right in the grid, then I can try to space/arrange them properly)
	std::map<std::string, SDL_Rect> row1Map;

	SDL_Rect a1 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect b1 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect c1 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect d1 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect e1 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect f1 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect g1 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect h1 = { 0, 0, squareSideSize, squareSideSize };

	// Add the rects to the map for row 1
	row1Map["A1"] = a1;
	row1Map["B1"] = b1;
	row1Map["C1"] = c1;
	row1Map["D1"] = d1;
	row1Map["E1"] = e1;
	row1Map["F1"] = f1;
	row1Map["G1"] = g1;
	row1Map["H1"] = h1;

	// Initialize the first row in the board grid vector
	std::vector<std::map<std::string, SDL_Rect>> row1Vect;
	row1Vect.push_back(row1Map);

	// Create the map of strings and rects for the second row
	std::map<std::string, SDL_Rect> row2Map;

	SDL_Rect a2 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect b2 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect c2 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect d2 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect e2 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect f2 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect g2 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect h2 = { 0, 0, squareSideSize, squareSideSize };

	// Add the rects to the map for row 2
	row2Map["A2"] = a2;
	row2Map["B2"] = b2;
	row2Map["C2"] = c2;
	row2Map["D2"] = d2;
	row2Map["E2"] = e2;
	row2Map["F2"] = f2;
	row2Map["G2"] = g2;
	row2Map["H2"] = h2;

	// Initialize the second row in the board grid vector
	std::vector<std::map<std::string, SDL_Rect>> row2Vect;
	row2Vect.push_back(row2Map);

	// Create the map of strings and rects for the third row
	std::map<std::string, SDL_Rect> row3Map;

	SDL_Rect a3 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect b3 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect c3 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect d3 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect e3 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect f3 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect g3 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect h3 = { 0, 0, squareSideSize, squareSideSize };

	// Add the rects to the map for row 3
	row3Map["A3"] = a3;
	row3Map["B3"] = b3;
	row3Map["C3"] = c3;
	row3Map["D3"] = d3;
	row3Map["E3"] = e3;
	row3Map["F3"] = f3;
	row3Map["G3"] = g3;
	row3Map["H3"] = h3;

	// Initialize the 3rd row in the board grid vector
	std::vector<std::map<std::string, SDL_Rect>> row3Vect;
	row3Vect.push_back(row3Map);

	// Create the map of strings and rects for the 4th row
	std::map<std::string, SDL_Rect> row4Map;

	SDL_Rect a4 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect b4 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect c4 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect d4 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect e4 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect f4 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect g4 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect h4 = { 0, 0, squareSideSize, squareSideSize };

	// Add the rects to the map for row 3
	row4Map["A4"] = a4;
	row4Map["B4"] = b4;
	row4Map["C4"] = c4;
	row4Map["D4"] = d4;
	row4Map["E4"] = e4;
	row4Map["F4"] = f4;
	row4Map["G4"] = g4;
	row4Map["H4"] = h4;

	// Initialize the 4th row in the board grid vector
	std::vector<std::map<std::string, SDL_Rect>> row4Vect;
	row4Vect.push_back(row4Map);
	
	// Create the map of strings and rects for the 5th row
	std::map<std::string, SDL_Rect> row5Map;

	SDL_Rect a5 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect b5 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect c5 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect d5 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect e5 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect f5 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect g5 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect h5 = { 0, 0, squareSideSize, squareSideSize };

	// Add the rects to the map for row 5
	row5Map["A5"] = a5;
	row5Map["B5"] = b5;
	row5Map["C5"] = c5;
	row5Map["D5"] = d5;
	row5Map["E5"] = e5;
	row5Map["F5"] = f5;
	row5Map["G5"] = g5;
	row5Map["H5"] = h5;

	// Initialize the 5th row in the board grid vector
	std::vector<std::map<std::string, SDL_Rect>> row5Vect;
	row5Vect.push_back(row5Map);
	
	// Create the map of strings and rects for the 6th row
	std::map<std::string, SDL_Rect> row6Map;

	SDL_Rect a6 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect b6 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect c6 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect d6 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect e6 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect f6 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect g6 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect h6 = { 0, 0, squareSideSize, squareSideSize };

	// Add the rects to the map for row 6
	row6Map["A6"] = a6;
	row6Map["B6"] = b6;
	row6Map["C6"] = c6;
	row6Map["D6"] = d6;
	row6Map["E6"] = e6;
	row6Map["F6"] = f6;
	row6Map["G6"] = g6;
	row6Map["H6"] = h6;

	// Initialize the 6th row in the board grid vector
	std::vector<std::map<std::string, SDL_Rect>> row6Vect;
	row6Vect.push_back(row6Map);
	
	// Create the map of strings and rects for the 7th row
	std::map<std::string, SDL_Rect> row7Map;

	SDL_Rect a7 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect b7 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect c7 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect d7 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect e7 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect f7 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect g7 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect h7 = { 0, 0, squareSideSize, squareSideSize };

	// Add the rects to the map for row 7
	row7Map["A7"] = a7;
	row7Map["B7"] = b7;
	row7Map["C7"] = c7;
	row7Map["D7"] = d7;
	row7Map["E7"] = e7;
	row7Map["F7"] = f7;
	row7Map["G7"] = g7;
	row7Map["H7"] = h7;

	// Initialize the 7th row in the board grid vector
	std::vector<std::map<std::string, SDL_Rect>> row7Vect;
	row7Vect.push_back(row7Map);
	
	// Create the map of strings and rects for the 8th row
	std::map<std::string, SDL_Rect> row8Map;

	SDL_Rect a8 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect b8 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect c8 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect d8 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect e8 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect f8 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect g8 = { 0, 0, squareSideSize, squareSideSize };
	SDL_Rect h8 = { 0, 0, squareSideSize, squareSideSize };

	// Add the rects to the map for row 8
	row8Map["A8"] = a8;
	row8Map["B8"] = b8;
	row8Map["C8"] = c8;
	row8Map["D8"] = d8;
	row8Map["E8"] = e8;
	row8Map["F8"] = f8;
	row8Map["G8"] = g8;
	row8Map["H8"] = h8;

	// Initialize the 8th row in the board grid vector
	std::vector<std::map<std::string, SDL_Rect>> row8Vect;
	row8Vect.push_back(row8Map);


	// Add the rows to the boardGrid. Because of FIFO, remember to do them in reverse order: row1Vect should be the last one in
	_boardGrid.push_back(row8Vect);
	_boardGrid.push_back(row7Vect);
	_boardGrid.push_back(row6Vect);
	_boardGrid.push_back(row5Vect);
	_boardGrid.push_back(row4Vect);
	_boardGrid.push_back(row3Vect);
	_boardGrid.push_back(row2Vect);
	_boardGrid.push_back(row1Vect);
	
	
		
	

}
