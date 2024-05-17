#include "GameScene.h"
#include "IdleGameState.h"

GameScene::GameScene() :
	_board(std::unique_ptr<Chessboard>(new Chessboard)),
	_pieces(),
	_playerOne(nullptr),
	_playerTwo(nullptr),
	_rules(std::unique_ptr<Rules>(new Rules)),
	_manager(std::unique_ptr<GameManager>(new GameManager)),
	_gsm(new GameStateMachine()),
	_currentState(&IdleGameState::getInstance()),
	_previousState(nullptr)
{
	assert(!_instantiated);
	_instantiated = true;
	_gsm->setGameScene(this);
	_pieces.reserve(32);
}