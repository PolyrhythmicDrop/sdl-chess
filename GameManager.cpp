#include "GameManager.h"
#include "easylogging++.h"

GameManager::GameManager(GameScene* gameScene) :
	_gameScene(gameScene),
	_history({}),
	_textAction(""),
	_textSetup("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"),
	_textPlacement(_textSetup)
{
	LOG(TRACE) << "Game Manager instantiated!";
}

void GameManager::parsePosition(std::string position)
{

}

void GameManager::setUpGame()
{
	// Get the board and the all the pieces

}
