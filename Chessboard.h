#pragma once
#include "Square.h"
#include "GraphicsComponent.h"
#include <vector>

class BoardIterator;

class Chessboard : public GameObject
{
private:

	// Grid that contains all the squares on the board
	std::vector<std::vector<Square>> _boardGrid;

public:

	Chessboard();
	// Copy constructor for deep copy
	Chessboard(const Chessboard& board);

	~Chessboard();

	inline SDL_Rect getBoardDimensions() const { return _dimensions; };
	inline std::vector<std::vector<Square>>* getBoardGrid() { return &_boardGrid; };
	void const printSquarePositions();

	void const buildChessboard();
	void const addBoardToRender();

	BoardIterator createIterator();
	
};

