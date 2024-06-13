#pragma once
#include "Square.h"
#include "GraphicsComponent.h"
#include <vector>

class Chessboard : public GameObject
{
private:

	// Grid that contains all the squares on the board
	std::vector<std::vector<Square>> _boardGrid;

	// Template for setting the positions for row squares
	void setRowSquarePosition(SDL_Point origin, std::vector<Square>& sqVect, int rowNum = 1);

public:

	Chessboard();
	// Copy constructor for deep copy
	Chessboard(const Chessboard& board);

	~Chessboard();

	Square createSquare(std::string name);

	inline SDL_Rect getBoardDimensions() const { return _dimensions; };
	inline std::vector<std::vector<Square>>* getBoardGrid() { return &_boardGrid; };
	void const printSquarePositions();
	Square* getSquareByName(std::string name);


	void const buildChessboard();
	void const addBoardToRender();
	
};

