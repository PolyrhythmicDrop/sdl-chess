#include "easylogging++.h"
#include "GameManager.h"
#include "GameScene.h"
#include "IdleGameState.h"
#include "InitGameState.h"
#include "PieceIterator.h"
#include "TurnBlackGameState.h"
#include "TurnWhiteGameState.h"
#include <thread>

GameManager::GameManager(GameScene* gameScene) :
	_gameScene(gameScene),
	_rules(std::make_unique<Rules>()),
	_gsm(std::make_unique<GameStateMachine>(this)),
	_currentTurn(NULL),
	_currentPlayer(NULL),
	_aiMode(false),
	_selectedPiece(nullptr),
	_highlightManager(std::make_unique<HighlightManager>(this)),
	_actionManager(std::make_unique<ActionManager>(this)),
	_selectionManager(std::make_unique<SelectionManager>(this)),
	_fishManager(std::make_unique<FishManager>(this)),
	_fenManager(std::make_unique<FenManager>(this)),
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
	
	if (eString == "pieceMove")
	{
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
		onPieceCapture(dynamic_cast <Piece*>(object));
	}
	else if (eString == "pieceRevived")
	{
		onPieceRevive(dynamic_cast <Piece*>(object));
	}
	else if (eString == "piecePassant")
	{
		FenPassantChange(dynamic_cast <Piece*>(object));
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

	if (eString == "startTurn")
	{
		onTurnStart();
	}
	if (eString == "undoAction")
	{
		_selectionManager->deselectPieces();
		_actionManager->clearUndoBuffer();
	}
	if (eString == "halfMoveReset")
	{
		_fenManager->resetFenHalfMove();
	}
}

void GameManager::fenToBoard(std::string position)
{

}

std::string GameManager::boardToFen()
{
	auto boardGrid = _gameScene->getBoard()->getBoardGrid();
	std::string fenPos = "";
	int emptySq = 0;

	for (int row = 7; row >= 0; --row)
	{		
		for (int col = 0; col < boardGrid->at(row).size(); ++col)
		{
			if (boardGrid->at(row).at(col).getOccupied())
			{
				if (emptySq > 0)
				{
					char emptyChar = '0' + emptySq;
					fenPos = fenPos + emptyChar;
					emptySq = 0;
				}
				char piece = boardGrid->at(row).at(col).getOccupant()->getFenName();
				fenPos = fenPos + piece;
			}
			else
			{
				++emptySq;
			}
		}
		if (emptySq > 0)
		{
			char emptyChar = '0' + emptySq;
			fenPos = fenPos + emptyChar;
			emptySq = 0;
		}
		fenPos = fenPos + '/';
	}

	// Remove the last forward slash from the string
	fenPos.pop_back();

	_fenManager->setFenPosition(fenPos);

	return fenPos;
}

void GameManager::setUpGame()
{
	setGameMode();
	setUpPlayers();
	setUpBoard();
	setUpPieces();
	setUpStockfish();
	return;
}

bool GameManager::setGameMode()
{
	bool gameSelect = false;
	// TODO: Create GUI for this. Put it in the console for now to test.
	while (!gameSelect)
	{
		std::cout << "Select your game mode:\n" << "1. Single Player\n" << "2. Head to Head\n";
		char choice;
		std::cin >> choice;

		try
		{
			switch (choice)
			{
			default:
				LOG(ERROR) << "Invalid choice!";
				throw choice;
				break;
			case '1':
				_aiMode = true;
				gameSelect = true;
				break;
			case '2':
				_aiMode = false;
				gameSelect = true;
				break;
			}
		}
		catch (char e)
		{
			LOG(ERROR) << e << " is an invalid choice! Try again.\n";
			continue;
		}
	}

}

void GameManager::setUpPlayers()
{
	// ** Player Initialization ** //
	std::string p1Name, p2Name;

	// Change the string depending on whether or not the player is playing against AI
	switch (_aiMode)
	{
	case false:
		std::cout << "Player One, enter your name:\n";
		std::cin >> p1Name;
		std::cout << "Player Two, enter your name:\n";
		std::cin >> p2Name;
		break;
	case true:
		std::cout << "Player One, enter your name:\n";
		std::cin >> p1Name;
		std::cout << "Enter a name for your AI opponent:\n";
		std::cin >> p2Name;
		break;
	}

	// TODO: Let the players select their color. For now, hard-coding Player One to be white and go first. 
	_gameScene->setPlayerOne(p1Name, 1, Player::HUMAN);
	_aiMode ? _gameScene->setPlayerTwo(p2Name, 0, Player::STOCKFISH) : _gameScene->setPlayerTwo(p2Name, 0, Player::HUMAN);

	// Set the current player to whoever chose white
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

void GameManager::setUpStockfish()
{
	/*_fishManager->initializeStockfish();*/
	_fishManager->newStockfishGame(_fenManager->createFishFen(_fenManager->createFenString(), false));
}

void GameManager::setTurn(bool color)
{
	_currentTurn = (int)color;

	// Set the current player to whoever's turn we're changing to.
	if (_gameScene->getPlayerOne()->getColor() == (int)color)
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

void GameManager::checkForCastle(Piece* king)
{
	bool rookLeftFirstMove = false;
	bool rookRightFirstMove = false;

	if (!_currentPlayer->getCheck())
	{
		if (king->getFirstMove())
		{
			// Get the current turn's rooks.
			char rook = 'R';
			switch (_currentTurn)
			{
			case 0:
				rook = 'r';
				break;
			case 1:
				rook = 'R';
				break;
			default:
				rook = 'R';
				break;
			}
			Piece* leftRook = nullptr;
			Piece* rightRook = nullptr;
			// Get living rooks of this turn and check whether or not it is their first move.
			for (Piece* p : _gameScene->getPieceContainer()->getPiecesByFen(rook))
			{
				if (p->isAlive() && p->getSquare()->getBoardIndex().second == 0)
				{
					rookLeftFirstMove = p->getFirstMove();
					leftRook = p;
				}
				else if (p->isAlive() && p->getSquare()->getBoardIndex().second == 7)
				{
					rookRightFirstMove = p->getFirstMove();
					rightRook = p;
				}
			}
			if (rookLeftFirstMove && rookRightFirstMove)
			{
				// Highlight castling for both the left and right rook.
				_highlightManager->highlightCastle(king, leftRook->getSquare(), rightRook->getSquare());
			}
			else if (rookLeftFirstMove && !rookRightFirstMove)
			{
				// Highlight castling for the left rook only.
				_highlightManager->highlightCastle(king, leftRook->getSquare());
			}
			else if (!rookLeftFirstMove && rookRightFirstMove)
			{
				// Highlight castling for the right rook only.
				_highlightManager->highlightCastle(king, nullptr, rightRook->getSquare());
			}
			else
			{
				// No rooks have their first move.
				return;
			}
		}
		else
		{
			// It was not the king's first move. Castling impossible.
			return;
		}
	}
	else
	{
		return;
	}
}

void GameManager::endTurn()
{
	fenTurnEnd();
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
				notify(pawn, "piecePassant");
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
				notify(pawn, "piecePassant");
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

	// Reset the half-move counter if a pawn moved.
	if (piece->getPieceType() == Piece::PAWN)
	{
		notify("halfMoveReset");
	}

	// Pawn promotion
	if (piece->isAlive() && piece->getSquare()->getBoardIndex().second == piece->getSquare()->getBoardIndex().second)
	{
		char promotion;
		if (piece->getFenName() == 'P' && piece->getSquare()->getBoardIndex().first == 7)
		{
			_actionManager->promotePawn(piece);
			promotion = piece->getFenName();
			_fenManager->addPromoteToFenMove(promotion);
		}
		else if (piece->getFenName() == 'p' && piece->getSquare()->getBoardIndex().first == 0)
		{
			_actionManager->promotePawn(piece);
			promotion = piece->getFenName();
			_fenManager->addPromoteToFenMove(promotion);
		}
	}

	_actionManager->clearUndoBuffer();
	endTurn();
	
}

void GameManager::onPieceCapture(Piece* piece)
{
	piece->setSquare(nullptr);
	// Add the piece to the captured piece location
	_gameScene->getPieceContainer()->addToCapturedPieces(piece);
	_gameScene->updateCaptureDump();
	LOG(INFO) << piece->getName() << " was captured!";
}

void GameManager::onPieceRevive(Piece* piece)
{
	_gameScene->getPieceContainer()->removePieceFromCapturedPieces(piece);
	_gameScene->updateCaptureDump();
	return;
}

void GameManager::onTurnStart()
{
	// Set the current turn for the GM and set the FEN string based on the current turn state
	if (_currentState == &TurnWhiteGameState::getInstance())
	{
		setTurn(1);
		_fenManager->setFenColor('w');
	}
	else if (_currentState == &TurnBlackGameState::getInstance())
	{
		setTurn(0);
		_fenManager->setFenColor('b');
	}

	// Set any active en passant flags for this color to false so that
	// any en passant captures must occur directly after pawn's first move
	endPassant();

	// Check for check. Set player check to false if player not in check. 
	// If this returns true, the player's check flag has already been set to true by the Highlight Manager,
	// so you do not need to set it here.
	if (_previousState != &InitGameState::getInstance())
	{
		if (!checkForCheck())
		{
			_currentPlayer->setCheck(false);
		}
		else
		{
			LOG(INFO) << _currentPlayer->getName() << " is in check! Be careful...";
		}
	}

	// Create a FEN string for the start of this turn
	setCurrentFen();

	// Return control to the state
	return;

}

void GameManager::fenTurnEnd()
{
	_fenManager->plusFenHalfMove();

	if (_currentTurn == 0)
	{
		_fenManager->plusFenFullMove();
	}

}

void GameManager::FenPassantChange(Piece* piece)
{
	// Set the FEN passant modifier
	std::string passantSqName;

	// Get the name of the square that will be passantable
	if (piece->getPieceColor() == Piece::BLACK)
	{
		passantSqName = _gameScene->getBoard()->getBoardGrid()->at(piece->getSquare()->getBoardIndex().first + 1).at(piece->getSquare()->getBoardIndex().second).getName();
	}
	else
	{
		passantSqName = _gameScene->getBoard()->getBoardGrid()->at(piece->getSquare()->getBoardIndex().first - 1).at(piece->getSquare()->getBoardIndex().second).getName();
	}

	// If the piece's en passant modifier has been set to TRUE, add the square to the list
	if (piece->getPassantable())
	{
		_fenManager->setFenPassant(passantSqName);
	}
	// If the piece's en passant modifier has been set to FALSE, remove the square from the list.
	else
	{
		_fenManager->removeFenPassantSquare(passantSqName);
	}
}

void GameManager::onStockfishTurn()
{
	// Set up FEN move string
	std::string lastPosition = *(_fenManager->getFenHistory()->rbegin() + 1);
	_fishManager->setLastMovePosition(_fenManager->createFishFen(lastPosition, true));
	_fishManager->setCurrentPosition(_fenManager->createFishFen(*(_fenManager->getFenHistory()->rbegin()), false));
	
	// Create new thread to run the Stockfish move and allow rendering to occur simultaneously
	std::thread fishThread(&GameManager::executeFishMove, this);
	fishThread.detach();
}

void GameManager::executeFishMove()
{

	// Calculate the best move and get the string pairs for that move
	std::pair<std::string, std::string> fishMove = _fishManager->parseBestMove(_fishManager->calculateFishMove());

	// Simulate fish click on piece
	Square& originSq = *_gameScene->getBoard()->getSquareByName(fishMove.first);
	_selectionManager->handleClickOnPiece(originSq.getOccupant());

	Sleep(500);

	// Simulate fish clicking on a square or opposing piece
	Square& targetSq = *_gameScene->getBoard()->getSquareByName(fishMove.second);
	if (targetSq.getOccupied())
	{
		_selectionManager->handleClickOnPiece(targetSq.getOccupant());
	}
	else
	{
		_selectionManager->handleClickOnEmptySquare(&targetSq);
	}

}

void GameManager::setCurrentFen()
{
	// Set the FEN board position
	boardToFen();
	// Combine the FEN castling modifiers
	_fenManager->updateFenCastle();
	// Combine all the existing FEN strings together.
	_fenManager->addToFenHistory(_fenManager->createFenString());
}


