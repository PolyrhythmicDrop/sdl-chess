#pragma once
#include "Stockfish.h"
#include <memory>

class GameManager;


class FishManager
{
	friend class GameManager;

private:

	std::shared_ptr<GameManager> _gm;
	std::unique_ptr<Stockfish> _stockfish;

	// The last position the board was in, including the move made from that position.
	std::string _lastPosition;
	// The current position of the board. Stockfish should ponder on this position for its move.
	std::string _currentPosition;

	std::string _moveOrigin;
	std::string _moveTarget;

	// The piece Stockfish wants to promote a pawn to
	char _promote;

public:

	FishManager(GameManager* gm);
	~FishManager() {};

	void newStockfishGame(std::string fen);

	void setUpStockfishPosition();

	void setLastMovePosition(std::string position);
	void setCurrentPosition(std::string position);

	// Get Stockfish's proposed best move using the FishManager's current position. 
	// The position supplied should be the board's position at the start of Stockfish's turn.
	std::string calculateFishMove();

	// Splits up the "best move" and adds the moves to the _moveOrigin and _moveTarget member variables
	// Returns a pair of strings. First = origin square, second = target square.
	std::pair<std::string, std::string> parseBestMove(std::string move);

	const char getPromote();

};

