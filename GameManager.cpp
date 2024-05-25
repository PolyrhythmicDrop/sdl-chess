#include "ActionManager.h"
#include "easylogging++.h"
#include "GameManager.h"
#include "GameScene.h"
#include "HighlightManager.h"
#include "TurnBlackGameState.h"
#include "TurnWhiteGameState.h"

GameManager::GameManager(GameScene* gameScene) :
	_gameScene(gameScene),
	_rules(std::make_unique<Rules>()),
	_currentTurn(NULL),
	_selectedPiece(nullptr),
	_history({}),
	_textAction(""),
	_textSetup("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"),
	_textPlacement(_textSetup),
	_highlightManager(std::make_unique<HighlightManager>(this)),
	_actionManager(std::make_unique<ActionManager>(this)),
	_selectionManager(std::make_unique<SelectionManager>(this))
{
	LOG(TRACE) << "Game Manager instantiated!";
}

template<typename Func>
void GameManager::boardGridLoop(Func f)
{
	for (int row = 0; row < _gameScene->getBoard()->getBoardGrid()->size(); ++row)
	{
		for (int col = 0; col < _gameScene->getBoard()->getBoardGrid()->at(row).size(); ++col)
		{
			f(row, col);
		}
	}
}

void GameManager::setMediators()
{

	// Add the GameManager as the mediator for the chessboard.
	this->_gameScene->getBoard()->setMediator(this);

	// Add the GameManager as the mediator for every square on the chessboard
	boardGridLoop([this](int row, int col) 
		{
			this->_gameScene->getBoard()->getBoardGrid()->at(row).at(col).setMediator(this);
		});

	// Add the GameManager as the mediator for all the pieces.
	for (int i = 0; i < this->_gameScene->getAllPieces()->size(); ++i)
	{
		this->_gameScene->getAllPieces()->at(i).setMediator(this);
	}
	
}

void GameManager::notify(GameObject* object, std::string eString)
{
	// If statements controlling what happens on each event

	// Piece notifications
	// ********************
	
	// A piece has changed the square it's on
	if (eString == "pieceMove")
	{
		LOG(DEBUG) << object->getName() << " has moved to square " << dynamic_cast <Piece*>(object)->getSquare()->getName();
		onPieceMove(dynamic_cast <Piece*>(object));
	}
	else if (eString == "pieceSelected")
	{
		LOG(INFO) << object->getName() << " on Square " << dynamic_cast <Piece*>(object)->getSquare()->getName() << " was selected!";
	}
	else if (eString == "pieceDeselected")
	{
		LOG(INFO) << object->getName() << " was deselected!";
	}

	// Square notifications
	// *********************

	if (eString == "squareOccupied")
	{
		LOG(DEBUG) << object->getName() << " has been occupied by " << dynamic_cast <Square*>(object)->getOccupant()->getFenName() << "!";
	}
	
}

void GameManager::notify(std::string eString)
{
	// Turn/State notifications
	// *************************

	if (eString == "turnChange")
	{
		if (_gameScene->getCurrentState() == &TurnWhiteGameState::getInstance())
		{
			setTurn(1);
		}
		else if (_gameScene->getCurrentState() == &TurnBlackGameState::getInstance())
		{
			setTurn(0);
		}
	}
}

void GameManager::parseFEN(std::string position)
{

}

void GameManager::setUpGame()
{
	// Add the Game Manager as the mediator for all the objects in the game scene
	this->setMediators();

	// *******************************
	// Set WHITE
	// Set the white pawns
	std::vector<int> pawnVect = _gameScene->getPiecesByFEN('P');
	for (int i = 0; i < pawnVect.size(); ++i)
	{
		_gameScene->getAllPieces()->at(pawnVect.at(i)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(1).at(i));
	}

	// Set the white rooks
	std::vector<int> rookVect = _gameScene->getPiecesByFEN('R');
	_gameScene->getAllPieces()->at(rookVect.at(0)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(0).at(0));
	_gameScene->getAllPieces()->at(rookVect.at(1)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(0).at(7));
	rookVect.clear();

	// Set the white knights
	std::vector<int> knightVect = _gameScene->getPiecesByFEN('N');
	_gameScene->getAllPieces()->at(knightVect.at(0)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(0).at(1));
	_gameScene->getAllPieces()->at(knightVect.at(1)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(0).at(6));
	knightVect.clear();

	// Set the white bishops
	std::vector<int> bishopVect = _gameScene->getPiecesByFEN('B');
	_gameScene->getAllPieces()->at(bishopVect.at(0)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(0).at(2));
	_gameScene->getAllPieces()->at(bishopVect.at(1)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(0).at(5));
	bishopVect.clear();

	// Set the white queen
	std::vector<int> queenVect = _gameScene->getPiecesByFEN('Q');
	_gameScene->getAllPieces()->at(queenVect.at(0)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(0).at(3));
	queenVect.clear();

	// Set the white king
	std::vector<int> kingVect = _gameScene->getPiecesByFEN('K');
	_gameScene->getAllPieces()->at(kingVect.at(0)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(0).at(4));
	kingVect.clear();
	// *****************************

	// *****************************
	// Set BLACK
	// Set the black pawns
	pawnVect = _gameScene->getPiecesByFEN('p');
	for (int i = 0; i < pawnVect.size(); ++i)
	{
		_gameScene->getAllPieces()->at(pawnVect.at(i)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(6).at(i));
	}

	// Set the black rooks
	rookVect = _gameScene->getPiecesByFEN('r');
	_gameScene->getAllPieces()->at(rookVect.at(0)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(7).at(0));
	_gameScene->getAllPieces()->at(rookVect.at(1)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(7).at(7));
	rookVect.clear();

	// Set the black knights
	knightVect = _gameScene->getPiecesByFEN('n');
	_gameScene->getAllPieces()->at(knightVect.at(0)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(7).at(1));
	_gameScene->getAllPieces()->at(knightVect.at(1)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(7).at(6));
	knightVect.clear();

	// Set the black bishops
	bishopVect = _gameScene->getPiecesByFEN('b');
	_gameScene->getAllPieces()->at(bishopVect.at(0)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(7).at(2));
	_gameScene->getAllPieces()->at(bishopVect.at(1)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(7).at(5));
	bishopVect.clear();

	// Set the black queen
	queenVect = _gameScene->getPiecesByFEN('q');
	_gameScene->getAllPieces()->at(queenVect.at(0)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(7).at(3));
	queenVect.clear();

	// Set the black king
	kingVect = _gameScene->getPiecesByFEN('k');
	_gameScene->getAllPieces()->at(kingVect.at(0)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(7).at(4));
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

void GameManager::setTurn(int turn)
{
	_currentTurn = turn;
}

void GameManager::handleClick()
{
	_selectionManager->handleClick();
}

void GameManager::onPieceMove(Piece* piece)
{
	_selectionManager->deselectPieces();

	// Pawn promotion
	if (_highlightManager->getPieceRules(piece).specialActions.promote)
	{
		_actionManager->promotePawn(piece);
	}

	// TODO: Check if move would put the player's king in check

	// TODO: Confirm if the player wants to end their turn?

	// End the turn
	endTurn();
}

void GameManager::endTurn()
{
	_gameScene->notify(this, "turnComplete");
}
