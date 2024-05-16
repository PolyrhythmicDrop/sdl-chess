#include "GameScene.h"
#include "InitGameState.h"

GameScene::GameScene() :
	_board(std::unique_ptr<Chessboard>(new Chessboard)),
	_pieces(),
	_playerOne(nullptr),
	_playerTwo(nullptr),
	_rules(std::unique_ptr<Rules>(new Rules)),
	_manager(std::unique_ptr<GameManager>(new GameManager)),
	_gsm(new GameStateMachine()),
	_currentState(&InitGameState::getInstance()),
	_previousState(nullptr)
{
	_pieces.reserve(32);
}