#pragma once
#include "Square.h"
#include <vector>

class Chessboard
{
private:

	GraphicsComponent* _graphics;

	enum BoardSkin {
		STANDARD
	};

	BoardSkin _skin;
	SDL_Rect _boardDimensions;

	// Grid that contains all the squares on the board
	std::vector<std::vector<Square>> _boardGrid;


public:

	Chessboard(BoardSkin skin = STANDARD);
	// Copy constructor for deep copy
	Chessboard(const Chessboard& board);

	~Chessboard();

	inline SDL_Rect getBoardDimensions() const { return _boardDimensions; };
	inline std::vector<std::vector<Square>> getBoardGrid() { return _boardGrid; };

	inline GraphicsComponent* getGraphics() const { return _graphics; };

	void const buildChessboard();
	
};

