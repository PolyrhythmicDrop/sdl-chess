#include "GameScene.h"
#include "IdleGameState.h"

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
}