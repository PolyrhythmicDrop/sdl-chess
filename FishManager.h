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

public:

	FishManager(GameManager* gm);
	~FishManager() {};

	void initializeStockfish();

	void newStockfishGame(std::string fen);

	void setLastPosition(std::string position);
	void setCurrentPosition(std::string position);

	// Sends the last position and the move made from that position to Stockfish.
	void sendLastPositionToFish();

	// Get Stockfish's proposed best move using the FishManager's current position. 
	// The position supplied should be the board's position at the start of Stockfish's turn.
	std::string getBestMove();

	void executeFishMove(std::string move);

};

