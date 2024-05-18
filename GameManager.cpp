#include "GameManager.h"
#include "easylogging++.h"
#include "GameScene.h"

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
	std::string name = _gameScene->getBoard()->getBoardGrid()->at(1).at(0).getName();

	// Debug getting the name
	LOG(INFO) << "The square on [1][0] is named: " << name;

	// Set the pawns
	_gameScene->getAllPieces()->at(0).setPosition(&_gameScene->getBoard()->getBoardGrid()->at(1).at(0));

	// Debug getting the name
	LOG(INFO) << "The square on [1][0] is named: " << _gameScene->getBoard()->getBoardGrid()->at(1).at(0).getName() << " and has the following piece on it: " << _gameScene->getBoard()->getBoardGrid()->at(1).at(0).getOccupant()->getFenName();

	// Attempt to add the pieces to the render queue
	std::vector<std::pair<GameObject*, SDL_Texture*>> rendVect;
	
	for (int i = 0; i < _gameScene->getAllPieces()->size(); ++i)
	{
		rendVect.push_back(std::pair<GameObject*, SDL_Texture*>(&_gameScene->getAllPieces()->at(i), _gameScene->getAllPieces()->at(i).getGraphics()->getSdlTexture()));
	}

	ServiceLocator::getGraphics().addToRenderMap(2, rendVect);

}
