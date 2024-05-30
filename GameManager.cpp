#include "ActionManager.h"
#include "easylogging++.h"
#include "GameManager.h"
#include "GameScene.h"
#include "HighlightManager.h"
#include "IdleGameState.h"
#include "TurnBlackGameState.h"
#include "TurnWhiteGameState.h"
#include "PieceIterator.h"

GameManager::GameManager(GameScene* gameScene) :
	_gameScene(gameScene),
	_rules(std::make_unique<Rules>()),
	_gsm(std::make_unique<GameStateMachine>(this)),
	_currentTurn(NULL),
	_currentPlayer(NULL),
	_selectedPiece(nullptr),
	_history({}),
	_textAction(""),
	_textSetup("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"),
	_textPlacement(_textSetup),
	_highlightManager(std::make_unique<HighlightManager>(this)),
	_actionManager(std::make_unique<ActionManager>(this)),
	_selectionManager(std::make_unique<SelectionManager>(this)),
	_currentState(&IdleGameState::getInstance()),
	_previousState(nullptr)
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

	PieceIterator pieceItr = _gameScene->getPieceContainer()->createIterator();

	// Add the GameManager as the mediator for all the pieces.
	for (pieceItr; !pieceItr.isDone(); pieceItr.goForward(1))
	{
		(*pieceItr.getCurrentPosition()).setMediator(this);
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
	else if (eString == "pieceCaptured")
	{
		// Set the piece's position to null
		dynamic_cast <Piece*>(object)->setSquare(nullptr);
		// Add the piece to the captured piece location
		_gameScene->getPieceContainer()->addToCapturedPieces(dynamic_cast <Piece*>(object));
		_gameScene->updateCaptureDump();
		LOG(INFO) << object->getName() << " was captured!";
	}
	else if (eString == "pieceRevived")
	{
		_gameScene->getPieceContainer()->removePieceFromCapturedPieces(dynamic_cast <Piece*>(object));
		_gameScene->updateCaptureDump();
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
		onTurnChange();
	}
	if (eString == "undoAction")
	{
		_selectionManager->deselectPieces();
		_actionManager->clearUndoBuffer();
	}
}

void GameManager::parseFEN(std::string position)
{

}

void GameManager::setUpGame()
{
	setUpPlayers();
	setUpBoard();
	setUpPieces();
}

void GameManager::setUpPlayers()
{
	// ** Player Initialization ** //
	std::string p1Name, p2Name;
	std::cout << "Player One, enter your name:\n";
	std::cin >> p1Name;
	std::cout << "Player Two, enter your name:\n";
	std::cin >> p2Name;

	// TODO: Let the players select their color. For now, hard-coding who goes first.
	_gameScene->setPlayerOne(p1Name, '1');
	_gameScene->setPlayerTwo(p2Name, '0');

	// Set the current player to whoever white is
	if (_gameScene->getPlayerOne()->getColor() == 1)
	{
		_currentPlayer = _gameScene->getPlayerOne();
	}
	else
	{
		_currentPlayer = _gameScene->getPlayerTwo();
	}

}

void GameManager::setUpBoard()
{

	// Build the chessboard squares and add the board grid to the render queue
	_gameScene->getBoard()->buildChessboard();
	LOG(TRACE) << "Chessboard squares and position constructed!";

	_gameScene->initializeCapturePoints();
	LOG(TRACE) << "Capture points built!";

	_gameScene->getBoard()->addBoardToRender();
	LOG(TRACE) << "Chessboard added to render queue!";

	// Add the current square positions to the debug log
	_gameScene->getBoard()->printSquarePositions();

}

void GameManager::setUpPieces()
{
	// Add the Game Manager as the mediator for all the objects in the game scene
	this->setMediators();

	// *******************************
	// Set WHITE
	// Set the white pawns
	std::vector<int> pawnVect = _gameScene->getPieceContainer()->getPieceIndexByFEN('P');
	for (int i = 0; i < pawnVect.size(); ++i)
	{
		_gameScene->getPieceContainer()->getAllPieces()->at(pawnVect.at(i)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(1).at(i));
	}

	// Set the white rooks
	std::vector<int> rookVect = _gameScene->getPieceContainer()->getPieceIndexByFEN('R');
	_gameScene->getPieceContainer()->getAllPieces()->at(rookVect.at(0)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(0).at(0));
	_gameScene->getPieceContainer()->getAllPieces()->at(rookVect.at(1)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(0).at(7));
	rookVect.clear();

	// Set the white knights
	std::vector<int> knightVect = _gameScene->getPieceContainer()->getPieceIndexByFEN('N');
	_gameScene->getPieceContainer()->getAllPieces()->at(knightVect.at(0)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(0).at(1));
	_gameScene->getPieceContainer()->getAllPieces()->at(knightVect.at(1)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(0).at(6));
	knightVect.clear();

	// Set the white bishops
	std::vector<int> bishopVect = _gameScene->getPieceContainer()->getPieceIndexByFEN('B');
	_gameScene->getPieceContainer()->getAllPieces()->at(bishopVect.at(0)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(0).at(2));
	_gameScene->getPieceContainer()->getAllPieces()->at(bishopVect.at(1)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(0).at(5));
	bishopVect.clear();

	// Set the white queen
	std::vector<int> queenVect = _gameScene->getPieceContainer()->getPieceIndexByFEN('Q');
	_gameScene->getPieceContainer()->getAllPieces()->at(queenVect.at(0)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(0).at(3));
	queenVect.clear();

	// Set the white king
	std::vector<int> kingVect = _gameScene->getPieceContainer()->getPieceIndexByFEN('K');
	_gameScene->getPieceContainer()->getAllPieces()->at(kingVect.at(0)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(0).at(4));
	kingVect.clear();
	// *****************************

	// *****************************
	// Set BLACK
	// Set the black pawns
	pawnVect = _gameScene->getPieceContainer()->getPieceIndexByFEN('p');
	for (int i = 0; i < pawnVect.size(); ++i)
	{
		_gameScene->getPieceContainer()->getAllPieces()->at(pawnVect.at(i)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(6).at(i));
	}

	// Set the black rooks
	rookVect = _gameScene->getPieceContainer()->getPieceIndexByFEN('r');
	_gameScene->getPieceContainer()->getAllPieces()->at(rookVect.at(0)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(7).at(0));
	_gameScene->getPieceContainer()->getAllPieces()->at(rookVect.at(1)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(7).at(7));
	rookVect.clear();

	// Set the black knights
	knightVect = _gameScene->getPieceContainer()->getPieceIndexByFEN('n');
	_gameScene->getPieceContainer()->getAllPieces()->at(knightVect.at(0)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(7).at(1));
	_gameScene->getPieceContainer()->getAllPieces()->at(knightVect.at(1)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(7).at(6));
	knightVect.clear();

	// Set the black bishops
	bishopVect = _gameScene->getPieceContainer()->getPieceIndexByFEN('b');
	_gameScene->getPieceContainer()->getAllPieces()->at(bishopVect.at(0)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(7).at(2));
	_gameScene->getPieceContainer()->getAllPieces()->at(bishopVect.at(1)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(7).at(5));
	bishopVect.clear();

	// Set the black queen
	queenVect = _gameScene->getPieceContainer()->getPieceIndexByFEN('q');
	_gameScene->getPieceContainer()->getAllPieces()->at(queenVect.at(0)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(7).at(3));
	queenVect.clear();

	// Set the black king
	kingVect = _gameScene->getPieceContainer()->getPieceIndexByFEN('k');
	_gameScene->getPieceContainer()->getAllPieces()->at(kingVect.at(0)).setSquare(&_gameScene->getBoard()->getBoardGrid()->at(7).at(4));
	kingVect.clear();
	// *****************************

	// ***********
	// Add the pieces to the render queue
	std::vector<std::pair<GameObject*, SDL_Texture*>> rendVect;
	PieceIterator pieceItr = _gameScene->getPieceContainer()->createIterator();
	
	for (int i = 0; i < pieceItr.getSize(); ++i)
	{
		pieceItr.goToIndex(i);
		rendVect.push_back(std::pair<GameObject*, SDL_Texture*>(&(*pieceItr.getCurrentPosition()), (*pieceItr.getCurrentPosition()).getGraphics()->getSdlTexture()));
	}

	ServiceLocator::getGraphics().addToRenderMap(2, rendVect);
	// ***********

}

void GameManager::setTurn(int turn)
{
	_currentTurn = turn;

	// Set the current player to whoever's turn we're changing to.
	if (_gameScene->getPlayerOne()->getColor() == turn)
	{
		_currentPlayer = _gameScene->getPlayerOne();
	}
	else
	{
		_currentPlayer = _gameScene->getPlayerTwo();
	}
	
}

bool GameManager::checkForCheck()
{
	// Find the square that the current turn's king is on.
	Square* kingSquare = nullptr;

	if (_currentTurn == 0)
	{
		kingSquare = _gameScene->getPieceContainer()->getPiecesByFen('k')[0]->getSquare();
	}
	else
	{
		kingSquare = _gameScene->getPieceContainer()->getPiecesByFen('K')[0]->getSquare();
	}

	// Pass the square the king is on to the highlight manager so it can perform check higlighting
	bool check = _highlightManager->highlightCheck(kingSquare);

	return check;

}

void GameManager::endTurn()
{
	_gsm->changeState(this, "changeTurn");
}

void GameManager::endPassant()
{
	if (_currentTurn == 0)
	{
		for (Piece* pawn : _gameScene->getPieceContainer()->getPiecesByFen('p'))
		{
			if (pawn->getPassantable())
			{
				pawn->setPassantable(false);
			}
		}
	}
	else
	{
		for (Piece* pawn : _gameScene->getPieceContainer()->getPiecesByFen('P'))
		{
			if (pawn->getPassantable())
			{
				pawn->setPassantable(false);
			}
		}
	}

}

void GameManager::handleClick()
{
	_selectionManager->handleClick();
}

void GameManager::onPieceMove(Piece* piece)
{
	_selectionManager->deselectPieces();

	// Pawn promotion
	if (piece->isAlive() && piece->getSquare()->getBoardIndex().second == piece->getSquare()->getBoardIndex().second)
	{
		if (piece->getFenName() == 'P' && piece->getSquare()->getBoardIndex().first == 7)
		{
			_actionManager->promotePawn(piece);
		}
		else if (piece->getFenName() == 'p' && piece->getSquare()->getBoardIndex().first == 0)
		{
			_actionManager->promotePawn(piece);
		}
	}

	_actionManager->clearUndoBuffer();
	endTurn();
	
}

void GameManager::onTurnChange()
{
	if (_currentState == &TurnWhiteGameState::getInstance())
	{
		setTurn(1);
	}
	else if (_currentState == &TurnBlackGameState::getInstance())
	{
		setTurn(0);
	}

	// Set any active en passant flags for this color to false so that any en passant captures must occur directly after pawn's first move
	endPassant();

	// Check for check. Set player check to false if player not in check. 
	// If this returns true, the player's check flag has already been set to true by the Highlight Manager, so you do not need to set it here.
	if (!checkForCheck())
	{
		_currentPlayer->setCheck(false);
	}
	else
	{
		LOG(INFO) << _currentPlayer->getName() << " is in check! Be careful...";
	}
}


