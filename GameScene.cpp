#include "GameScene.h"
#include "IdleGameState.h"
#include "easylogging++.h"

GameScene::GameScene() :
	_board(std::unique_ptr<Chessboard>(new Chessboard)),
	_pieces(),
	_playerOne(nullptr),
	_playerTwo(nullptr),
	_rules(std::unique_ptr<Rules>(new Rules)),
	_manager(nullptr),
	_gsm(new GameStateMachine()),
	_currentState(&IdleGameState::getInstance()),
	_previousState(nullptr)
{
	assert(!_instantiated);
	_instantiated = true;
	_manager.reset(new GameManager(this));
	_gsm->setGameScene(this);
	_pieces.reserve(32);
	initializePieces();

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
	
	_pieces.push_back(whtPawn);
	_pieces.push_back(whtPawn);
	_pieces.push_back(whtPawn);
	_pieces.push_back(whtPawn);
	_pieces.push_back(whtPawn);
	_pieces.push_back(whtPawn);
	_pieces.push_back(whtPawn);
	_pieces.push_back(whtPawn);

	Piece whtRook(Piece::ROOK, Piece::WHITE);

	_pieces.push_back(whtRook);
	_pieces.push_back(whtRook);

	Piece whtKnight(Piece::KNIGHT, Piece::WHITE);

	_pieces.push_back(whtKnight);
	_pieces.push_back(whtKnight);

	Piece whtBishop(Piece::BISHOP, Piece::WHITE);

	_pieces.push_back(whtBishop);
	_pieces.push_back(whtBishop);

	Piece whtQueen(Piece::QUEEN, Piece::WHITE);

	_pieces.push_back(whtQueen);

	Piece whtKing(Piece::KING, Piece::WHITE);

	_pieces.push_back(whtKing);
	
	// Instantiate the black pieces and add them to the _pieces vector
	Piece blkPawn(Piece::PAWN, Piece::BLACK);

	_pieces.push_back(blkPawn);
	_pieces.push_back(blkPawn);
	_pieces.push_back(blkPawn);
	_pieces.push_back(blkPawn);
	_pieces.push_back(blkPawn);
	_pieces.push_back(blkPawn);
	_pieces.push_back(blkPawn);
	_pieces.push_back(blkPawn);

	Piece blkRook(Piece::ROOK, Piece::BLACK);

	_pieces.push_back(blkRook);
	_pieces.push_back(blkRook);

	Piece blkKnight(Piece::KNIGHT, Piece::BLACK);

	_pieces.push_back(blkKnight);
	_pieces.push_back(blkKnight);

	Piece blkBishop(Piece::BISHOP, Piece::BLACK);

	_pieces.push_back(blkBishop);
	_pieces.push_back(blkBishop);

	Piece blkQueen(Piece::QUEEN, Piece::BLACK);

	_pieces.push_back(blkQueen);

	Piece blkKing(Piece::KING, Piece::BLACK);

	_pieces.push_back(blkKing);

	LOG(TRACE) << _pieces.size() << " pieces added to Game Scene!";

}