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
	// *******************************
	// Set WHITE
	// Set the white pawns
	std::vector<int> pawnVect = _gameScene->getPiecesByFEN('P');
	for (int i = 0; i < pawnVect.size(); ++i)
	{
		_gameScene->getAllPieces()->at(pawnVect.at(i)).setPosition(&_gameScene->getBoard()->getBoardGrid()->at(1).at(i));
	}

	// Set the white rooks
	std::vector<int> rookVect = _gameScene->getPiecesByFEN('R');
	_gameScene->getAllPieces()->at(rookVect.at(0)).setPosition(&_gameScene->getBoard()->getBoardGrid()->at(0).at(0));
	_gameScene->getAllPieces()->at(rookVect.at(1)).setPosition(&_gameScene->getBoard()->getBoardGrid()->at(0).at(7));
	rookVect.clear();

	// Set the white knights
	std::vector<int> knightVect = _gameScene->getPiecesByFEN('N');
	_gameScene->getAllPieces()->at(knightVect.at(0)).setPosition(&_gameScene->getBoard()->getBoardGrid()->at(0).at(1));
	_gameScene->getAllPieces()->at(knightVect.at(1)).setPosition(&_gameScene->getBoard()->getBoardGrid()->at(0).at(6));
	knightVect.clear();

	// Set the white bishops
	std::vector<int> bishopVect = _gameScene->getPiecesByFEN('B');
	_gameScene->getAllPieces()->at(bishopVect.at(0)).setPosition(&_gameScene->getBoard()->getBoardGrid()->at(0).at(2));
	_gameScene->getAllPieces()->at(bishopVect.at(1)).setPosition(&_gameScene->getBoard()->getBoardGrid()->at(0).at(5));
	bishopVect.clear();

	// Set the white queen
	std::vector<int> queenVect = _gameScene->getPiecesByFEN('Q');
	_gameScene->getAllPieces()->at(queenVect.at(0)).setPosition(&_gameScene->getBoard()->getBoardGrid()->at(0).at(3));
	queenVect.clear();

	// Set the white king
	std::vector<int> kingVect = _gameScene->getPiecesByFEN('K');
	_gameScene->getAllPieces()->at(kingVect.at(0)).setPosition(&_gameScene->getBoard()->getBoardGrid()->at(0).at(4));
	kingVect.clear();
	// *****************************

	// *****************************
	// Set BLACK
	// Set the black pawns
	pawnVect = _gameScene->getPiecesByFEN('p');
	for (int i = 0; i < pawnVect.size(); ++i)
	{
		_gameScene->getAllPieces()->at(pawnVect.at(i)).setPosition(&_gameScene->getBoard()->getBoardGrid()->at(6).at(i));
	}

	// Set the black rooks
	rookVect = _gameScene->getPiecesByFEN('r');
	_gameScene->getAllPieces()->at(rookVect.at(0)).setPosition(&_gameScene->getBoard()->getBoardGrid()->at(7).at(0));
	_gameScene->getAllPieces()->at(rookVect.at(1)).setPosition(&_gameScene->getBoard()->getBoardGrid()->at(7).at(7));
	rookVect.clear();

	// Set the black knights
	knightVect = _gameScene->getPiecesByFEN('n');
	_gameScene->getAllPieces()->at(knightVect.at(0)).setPosition(&_gameScene->getBoard()->getBoardGrid()->at(7).at(1));
	_gameScene->getAllPieces()->at(knightVect.at(1)).setPosition(&_gameScene->getBoard()->getBoardGrid()->at(7).at(6));
	knightVect.clear();

	// Set the black bishops
	bishopVect = _gameScene->getPiecesByFEN('b');
	_gameScene->getAllPieces()->at(bishopVect.at(0)).setPosition(&_gameScene->getBoard()->getBoardGrid()->at(7).at(2));
	_gameScene->getAllPieces()->at(bishopVect.at(1)).setPosition(&_gameScene->getBoard()->getBoardGrid()->at(7).at(5));
	bishopVect.clear();

	// Set the black queen
	queenVect = _gameScene->getPiecesByFEN('q');
	_gameScene->getAllPieces()->at(queenVect.at(0)).setPosition(&_gameScene->getBoard()->getBoardGrid()->at(7).at(3));
	queenVect.clear();

	// Set the black king
	kingVect = _gameScene->getPiecesByFEN('k');
	_gameScene->getAllPieces()->at(kingVect.at(0)).setPosition(&_gameScene->getBoard()->getBoardGrid()->at(7).at(4));
	kingVect.clear();
	// *****************************

	// ***********
	// Add the pieces to the render queue
	std::vector<std::pair<GameObject*, SDL_Texture*>> rendVect;
	
	for (int i = 0; i < _gameScene->getAllPieces()->size(); ++i)
	{
		rendVect.push_back(std::pair<GameObject*, SDL_Texture*>(&_gameScene->getAllPieces()->at(i), _gameScene->getAllPieces()->at(i).getGraphics()->getSdlTexture()));
	}

	ServiceLocator::getGraphics().addToRenderMap(2, rendVect);
	// ***********

}
