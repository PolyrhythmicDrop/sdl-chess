#include "FishManager.h"
#include "GameManager.h"
#include "easylogging++.h"

FishManager::FishManager(GameManager* gm) :
	_gm(gm),
	_stockfish(std::make_unique<Stockfish>()),
	_lastPosition(""),
	_promote(NULL)
{}

void FishManager::newStockfishGame(std::string fen)
{
	_stockfish.get()->newGameStockfish(fen);
}

void FishManager::setUpStockfishPosition()
{
	// Set up FEN move string
	if (_lastPosition == "" || _gm->_fenManager->getFenHistory()->size() != 0)
	{
		std::string lastPosition = *(_gm->_fenManager->getFenHistory()->rbegin() + 1);
		setLastMovePosition(_gm->_fenManager->createFishFen(lastPosition, true));
	}
	setCurrentPosition(_gm->_fenManager->createFishFen(*(_gm->_fenManager->getFenHistory()->rbegin()), false));
}

void FishManager::setLastMovePosition(std::string position)
{
	_lastPosition = position;
	LOG(TRACE) << "Stockfish Last Position: " << _lastPosition;
}

void FishManager::setCurrentPosition(std::string position)
{
	_currentPosition = position;
	LOG(TRACE) << "Stockfish Current Position: " << _currentPosition;
}

std::string FishManager::calculateFishMove()
{
	std::string bestMove{};

	// Query Stockfish to see if it's ready
	while (!_stockfish->isStockfishReady())
	{
		LOG(TRACE) << "Waiting...";
		Sleep(500);
	}

	_stockfish->commandStockfish(_lastPosition);

	_stockfish->commandStockfish(_currentPosition);

	// Tell Stockfish to start calculating a move
	_stockfish->commandStockfish("go depth 20");

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

std::pair<std::string, std::string> FishManager::parseBestMove(std::string move)
{
	std::string::iterator moveItr = move.begin();
	std::advance(moveItr, 9);
	auto bestItr = std::find(moveItr, move.end(), ' ');
	__int64 distance = std::distance(moveItr, bestItr);

	std::string fullMove = move.substr(9, distance);
	std::string sq1 = fullMove.substr(0, 2);
	std::string sq2 = fullMove.substr(2, 2);

	if (fullMove.size() > 4)
	{
		char promo = (*fullMove.rbegin());
		_promote = promo;
	}

	_moveOrigin = sq1;
	_moveTarget = sq2;

	std::pair<std::string, std::string> bestMove = { sq1, sq2 };

	return bestMove;
}

const char FishManager::getPromote()
{
	return _promote;
}