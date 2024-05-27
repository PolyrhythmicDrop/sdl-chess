#include "GameScene.h"
#include "easylogging++.h"

GameScene::GameScene() :
	_board(std::unique_ptr<Chessboard>(new Chessboard)),
	_pieceContainer(PieceContainer()),
	_playerOne(Player("", ' ')),
	_playerTwo(Player("", ' ')),
	_manager(std::make_unique<GameManager>(this))	
{
	assert(!_instantiated);
	_instantiated = true;

	LOG(TRACE) << "Game Scene initialized!";
}

GameScene::~GameScene()
{
	LOG(TRACE) << "Game Scene destructed!";
}

void GameScene::initializeCapturePoints()
{
	_whiteCapturePoint = { (_board->getX() - (_board->getWidth() / 4)), (_board->getY() + (_board->getHeight() / 8)) };
	_blackCapturePoint = { ((_board->getX() + _board->getWidth()) + (_board->getWidth() / 8)), ((_board->getY() + _board->getHeight()) - (_board->getHeight() / 8)) };
}

void GameScene::addToCapturedPieces(Piece* piece)
{
	if (piece->isAlive() == false)
	{
		_pieceContainer._capturedPieces[piece->getPieceColor()].push_back(piece);
	}

	// Move captured pieces to the garbage dump
	for (int i = 0; i < _pieceContainer._capturedPieces[0].size(); ++i)
	{
		_pieceContainer._capturedPieces[0].at(i)->setPosition(_blackCapturePoint.x, _blackCapturePoint.y - (i * (_board->getHeight() / 16)));
	}
	for (int i = 0; i < _pieceContainer._capturedPieces[1].size(); ++i)
	{
		_pieceContainer._capturedPieces[1].at(i)->setPosition(_whiteCapturePoint.x, _whiteCapturePoint.y - (i * 50));
	}
}