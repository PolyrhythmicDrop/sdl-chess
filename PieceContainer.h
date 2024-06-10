#pragma once
#include <vector>
#include "Piece.h"

class PieceIterator;

class PieceContainer
{
	friend class PieceIterator;
	friend class GameScene;

private:

	std::vector<Piece> _pieces;

	// Captured pieces go here.
	// Key is the color of the piece. 0 = Black, 1 = White.
	std::vector<Piece*> _capturedPieces;

public:

	PieceContainer();
	~PieceContainer() {};

	PieceIterator createIterator();

	void initializePieces(std::string fen);

	// Returns a pointer to the piece vector
	inline std::vector<Piece>* getAllPieces() { return &_pieces; };

	// Gets the index in the pieces vector of all the pieces with the specified FEN name.
	std::vector<int> getPieceIndexByFEN(char fen);
	// Returns a vector of pointers to the pieces with the specified FEN name.
	std::vector<Piece*> getPiecesByFen(char fen);

	void addToCapturedPieces(Piece* piece);
	// Gets all the captured pieces for the specified color.
	// 0 = Black, 1 = White
	std::vector<Piece*> getCapturedPiecesByColor(int color);
	// Returns the last piece that was captured.
	Piece* getLastCapturedPiece();
	// Removes a piece from the captured pieces vector.
	void removePieceFromCapturedPieces(Piece* piece);

};

