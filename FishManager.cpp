#include "FishManager.h"
#include "GameManager.h"
#include "easylogging++.h"

FishManager::FishManager(GameManager* gm) :
	_gm(gm),
	_stockfish(std::make_unique<Stockfish>())
{}

void FishManager::initializeStockfish()
{
	_stockfish.get()->createStockfishProcess();
}

void FishManager::newStockfishGame(std::string fen)
{
	_stockfish.get()->newGameStockfish(fen);
}

void FishManager::setLastPosition(std::string position)
{
	_lastPosition = position;
}

void FishManager::setCurrentPosition(std::string position)
{
	_currentPosition = position;
}

void FishManager::sendLastPositionToFish()
{
	// Query Stockfish to see if it's ready
	while (!_stockfish->isStockfishReady())
	{
		LOG(TRACE) << "Waiting...";
		Sleep(500);
	}

	_stockfish->commandStockfish(_lastPosition);
}

std::string FishManager::getBestMove()
{
	std::string bestMove = "";

	// Query Stockfish to see if it's ready
	while (!_stockfish->isStockfishReady())
	{
		LOG(TRACE) << "Waiting...";
		Sleep(500);
	}

	// Send the last board position & the move from that position to Stockfish
	sendLastPositionToFish();

	// Send the current board position to Stockfish
	_stockfish->commandStockfish(_currentPosition);

	// Tell Stockfish to start calculating a move
	_stockfish->commandStockfish("go depth 10");

	// Wait until Stockfish returns "bestmove"
	while (!_stockfish->waitForBestMove())
	{
		LOG(TRACE) << "Waiting for best move...";
		Sleep(500);
	}

	bestMove = _stockfish->_bestMove;

	LOG(TRACE) << bestMove;

	return bestMove;
}