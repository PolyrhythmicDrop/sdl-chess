#include "GameScene.h"
#include "IdleGameState.h"
#include "easylogging++.h"

GameScene::GameScene() :
	_board(std::unique_ptr<Chessboard>(new Chessboard)),
	_pieces(),
	_capturedPieces(),
	_playerOne(Player("", ' ')),
	_playerTwo(Player("", ' ')),
	_manager(std::make_unique<GameManager>(this)),
	_gsm(std::make_unique<GameStateMachine>(this)),
	_currentState(&IdleGameState::getInstance()),
	_previousState(nullptr)
{
	assert(!_instantiated);
	_instantiated = true;
	_pieces.reserve(32);
	initializePieces();
	_capturedPieces[0].clear();
	_capturedPieces[1].clear();

	LOG(TRACE) << "Game Scene initialized!";
}

GameScene::~GameScene()
{
	LOG(TRACE) << "Game Scene destructed!";
}

void GameScene::initializePieces()
{
	// Instantiate the white pieces and add them to the _pieces vector
	Piece whtPawn(Piece::PAWN, Piece::WHITE);
	Piece whtPawn1(Piece::PAWN, Piece::WHITE);
	Piece whtPawn2(Piece::PAWN, Piece::WHITE);
	Piece whtPawn3(Piece::PAWN, Piece::WHITE);
	Piece whtPawn4(Piece::PAWN, Piece::WHITE);
	Piece whtPawn5(Piece::PAWN, Piece::WHITE);
	Piece whtPawn6(Piece::PAWN, Piece::WHITE);
	Piece whtPawn7(Piece::PAWN, Piece::WHITE);

		
	_pieces.push_back(whtPawn);
	_pieces.push_back(whtPawn1);
	_pieces.push_back(whtPawn2);
	_pieces.push_back(whtPawn3);
	_pieces.push_back(whtPawn4);
	_pieces.push_back(whtPawn5);
	_pieces.push_back(whtPawn6);
	_pieces.push_back(whtPawn7);

	Piece whtRook(Piece::ROOK, Piece::WHITE);
	Piece whtRook1(Piece::ROOK, Piece::WHITE);

	_pieces.push_back(whtRook);
	_pieces.push_back(whtRook1);

	Piece whtKnight(Piece::KNIGHT, Piece::WHITE);
	Piece whtKnight1(Piece::KNIGHT, Piece::WHITE);

	_pieces.push_back(whtKnight);
	_pieces.push_back(whtKnight1);

	Piece whtBishop(Piece::BISHOP, Piece::WHITE);
	Piece whtBishop1(Piece::BISHOP, Piece::WHITE);

	_pieces.push_back(whtBishop);
	_pieces.push_back(whtBishop1);

	Piece whtQueen(Piece::QUEEN, Piece::WHITE);

	_pieces.push_back(whtQueen);

	Piece whtKing(Piece::KING, Piece::WHITE);

	_pieces.push_back(whtKing);
	
	// Instantiate the black pieces and add them to the _pieces vector
	Piece blkPawn(Piece::PAWN, Piece::BLACK);
	Piece blkPawn1(Piece::PAWN, Piece::BLACK);
	Piece blkPawn2(Piece::PAWN, Piece::BLACK);
	Piece blkPawn3(Piece::PAWN, Piece::BLACK);
	Piece blkPawn4(Piece::PAWN, Piece::BLACK);
	Piece blkPawn5(Piece::PAWN, Piece::BLACK);
	Piece blkPawn6(Piece::PAWN, Piece::BLACK);
	Piece blkPawn7(Piece::PAWN, Piece::BLACK);

	_pieces.push_back(blkPawn);
	_pieces.push_back(blkPawn1);
	_pieces.push_back(blkPawn2);
	_pieces.push_back(blkPawn3);
	_pieces.push_back(blkPawn4);
	_pieces.push_back(blkPawn5);
	_pieces.push_back(blkPawn6);
	_pieces.push_back(blkPawn7);

	Piece blkRook(Piece::ROOK, Piece::BLACK);
	Piece blkRook1(Piece::ROOK, Piece::BLACK);

	_pieces.push_back(blkRook);
	_pieces.push_back(blkRook1);

	Piece blkKnight(Piece::KNIGHT, Piece::BLACK);
	Piece blkKnight1(Piece::KNIGHT, Piece::BLACK);

	_pieces.push_back(blkKnight);
	_pieces.push_back(blkKnight1);

	Piece blkBishop(Piece::BISHOP, Piece::BLACK);
	Piece blkBishop1(Piece::BISHOP, Piece::BLACK);

	_pieces.push_back(blkBishop);
	_pieces.push_back(blkBishop1);

	Piece blkQueen(Piece::QUEEN, Piece::BLACK);

	_pieces.push_back(blkQueen);

	Piece blkKing(Piece::KING, Piece::BLACK);

	_pieces.push_back(blkKing);

	LOG(TRACE) << _pieces.size() << " pieces added to Game Scene!";

}

void GameScene::initializeCapturePoints()
{
	_whiteCapturePoint = { (_board->getX() - (_board->getWidth() / 4)), (_board->getY() + (_board->getHeight() / 8)) };
	_blackCapturePoint = { ((_board->getX() + _board->getWidth()) + (_board->getWidth() / 8)), ((_board->getY() + _board->getHeight()) - (_board->getHeight() / 8)) };
}

std::vector<int> GameScene::getPiecesByFEN(char fen)
{
	
	std::vector<int> foundPieceIndexes;
	// Create an iterator for the Piece vector
	std::vector<Piece>::iterator itr = _pieces.begin();

	do
	{
		itr = std::find_if(itr, _pieces.end(), [&](Piece piece) {
			return piece.getFenName() == fen;
			});
		if (itr != _pieces.end())
		{
			int index = std::distance(_pieces.begin(), itr);
			foundPieceIndexes.push_back(index);
			itr++;
		}
		else
		{
			break;
		}
	} while (itr != _pieces.end());

	return foundPieceIndexes;

}

std::vector<Piece*> GameScene::getCapturedPieces(int color)
{
	return _capturedPieces[color];
}

void GameScene::addToCapturedPieces(Piece* piece)
{
	if (piece->isAlive() == false)
	{
		_capturedPieces[piece->getPieceColor()].push_back(piece);
	}

	// Move captured pieces to the garbage dump
	for (int i = 0; i < _capturedPieces[0].size(); ++i)
	{
		_capturedPieces[0].at(i)->setPosition(_blackCapturePoint.x, _blackCapturePoint.y - (i * (_board->getHeight() / 16)));
	}
	for (int i = 0; i < _capturedPieces[1].size(); ++i)
	{
		_capturedPieces[1].at(i)->setPosition(_whiteCapturePoint.x, _whiteCapturePoint.y - (i * 50));
	}
}