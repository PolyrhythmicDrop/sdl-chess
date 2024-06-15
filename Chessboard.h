#pragma once
#include "Square.h"
#include <vector>

class Chessboard : public GameObject
{
private:

	// Grid that contains all the squares on the board
	std::vector<std::vector<Square>> _boardGrid;

	void initializeBoardGrid();

	SDL_Point setBoardDimensionsToWindow();

	// Set the positions for row squares
	void setRowSquarePosition(SDL_Point origin, std::vector<Square>& sqVect, int rowNum = 1);

	void setRowTileType(bool odd, std::vector<Square>& sqVect);

public:

	Chessboard();
	// Copy constructor for deep copy
	Chessboard(const Chessboard& board);

	~Chessboard();

	Square createSquare(const std::string& name);

	inline SDL_Rect getBoardDimensions() const { return _dimensions; };
	inline std::vector<std::vector<Square>>* getBoardGrid() { return &_boardGrid; };
	void const printSquarePositions();
	std::shared_ptr<Square> getSquareByName(const std::string& name);

	void const buildChessboard();
	void const addBoardToRender();
	
};

