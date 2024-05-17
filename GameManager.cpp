#include "GameManager.h"
#include "easylogging++.h"

GameManager::GameManager(GameScene* gameScene) :
	_gameScene(gameScene)
{
	LOG(TRACE) << "Game Manager instantiated!";
}

