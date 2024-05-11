#pragma once
#include "GraphicsComponent.h"
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

	// A vector of vectors (2D vector) that contains the board grid, with rows and columns and a string name for each rectangle
	std::vector<std::vector<std::map<std::string, SDL_Rect>>> _boardGrid;


public:

	Chessboard(BoardSkin skin = STANDARD);
	~Chessboard();

	inline SDL_Rect getBoardDimensions() const { return _boardDimensions; };

	inline GraphicsComponent* getGraphics() const { return _graphics; };

	void buildChessboard();
	
};

