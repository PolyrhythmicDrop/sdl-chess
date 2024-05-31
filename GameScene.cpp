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
	_whiteCapturePoint = { (_board->getX() - (_board->getWidth() / 6)), _board->getY() };
	_blackCapturePoint = { ((_board->getX() + _board->getWidth()) + (_board->getWidth() / 32)), (_board->getY() + _board->getHeight()) - (_board->getWidth() / 8) };
}

void GameScene::updateCaptureDump()
{
	int dumpBlk = 0;
	int dumpWht = 0;
	int dumpOffset = _board->getHeight() / 16;

	// Move captured pieces to the garbage dump
	for (int i = 0; i < _pieceContainer._capturedPieces.size(); ++i)
	{
		if (_pieceContainer._capturedPieces.at(i)->getPieceColor() == 0)
		{
			_pieceContainer._capturedPieces.at(i)->setPosition(_blackCapturePoint.x, _blackCapturePoint.y - dumpBlk);
			dumpBlk = dumpBlk + dumpOffset;
		}
		else if (_pieceContainer._capturedPieces.at(i)->getPieceColor() == 1)
		{
			_pieceContainer._capturedPieces.at(i)->setPosition(_whiteCapturePoint.x, _whiteCapturePoint.y + dumpWht);
			dumpWht = dumpWht + dumpOffset;
		}
	}
}

void GameScene::setPlayerOne(std::string name, int color)
{ 
	_playerOne.setName(name);
	_playerOne.setColor(color); 
}

void GameScene::setPlayerTwo(std::string name, int color)
{
	_playerTwo.setName(name);
	_playerTwo.setColor(color); 
}