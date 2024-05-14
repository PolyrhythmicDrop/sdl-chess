#pragma once
#include "Square.h"
#include "GraphicsComponent.h"
#include <vector>

class Chessboard : public GameObject
{
private:

	GraphicsComponent* _graphics;

	enum BoardSkin {
		STANDARD
	};

	BoardSkin _skin;

	// Grid that contains all the squares on the board
	std::vector<std::vector<Square>> _boardGrid;


public:

	Chessboard(BoardSkin skin = STANDARD);
	// Copy constructor for deep copy
	Chessboard(const Chessboard& board);

	~Chessboard();

	inline SDL_Rect getBoardDimensions() const { return _dimensions; };
	inline std::vector<std::vector<Square>> getBoardGrid() { return _boardGrid; };

	inline GraphicsComponent* getGraphics() const { return _graphics; };

	void const buildChessboard();
	
};

