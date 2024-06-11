#include "easylogging++.h"
#include "GameManager.h"
#include "GameScene.h"
#include "IdleGameState.h"
#include "InitGameState.h"
#include "EndGameState.h"
#include "PieceIterator.h"
#include "TurnBlackGameState.h"
#include "TurnWhiteGameState.h"
#include <thread>

GameManager::GameManager(GameScene* gameScene) :
	_gameScene(gameScene),
	_rules(std::make_unique<Rules>()),
	_gsm(std::make_unique<GameStateMachine>(this)),
	_currentTurn(0),
	_currentPlayer(nullptr),
	_previousPlayer(nullptr),
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
	const auto& boardGrid = _gameScene->getBoard()->getBoardGrid();
	std::string fenPos{};
	int emptySq{ 0 };

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
	// Use the default starting position for now, supply a custom FEN as argument later
	setUpScenario("r3kbnr/p1p1pppp/n7/N7/1PPq4/8/4KPPP/2q2BNR b kq - 0 16");
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

std::string GameManager::setUpScenario(std::string fen)
{
	// Put in error checking later
	_fenManager->parseFenString(fen);
	_fenManager->_fenColor == 'w' ? setTurn(1) : setTurn(0);
	return _fenManager->_fenString;
}

void GameManager::setUpPieces()
{

	_gameScene->getPieceContainer()->initializePieces(_fenManager->_fenPosition);

	// Add the Game Manager as the mediator for all the objects in the game scene
	setMediators();

	// Creation of piece vectors and iterators for the individual pieces

	const auto& pieces = _gameScene->getPieceContainer();

	const auto& blkPawnVect = pieces->getPiecesByFen('p');
	std::vector<Piece*>::const_iterator blkPawnItr = blkPawnVect.begin();

	const auto& whtPawnVect = pieces->getPiecesByFen('P');
	std::vector<Piece*>::const_iterator whtPawnItr = whtPawnVect.begin();

	const auto& blkRookVect = pieces->getPiecesByFen('r');
	std::vector<Piece*>::const_iterator blkRookItr = blkRookVect.begin();

	const auto& whtRookVect = pieces->getPiecesByFen('R');
	std::vector<Piece*>::const_iterator whtRookItr = whtRookVect.begin();

	const auto& blkKnightVect = pieces->getPiecesByFen('n');
	std::vector<Piece*>::const_iterator blkKnightItr = blkKnightVect.begin();

	const auto& whtKnightVect = pieces->getPiecesByFen('N');
	std::vector<Piece*>::const_iterator whtKnightItr = whtKnightVect.begin();

	const auto& blkBishopVect = pieces->getPiecesByFen('b');
	std::vector<Piece*>::const_iterator blkBishopItr = blkBishopVect.begin();

	const auto& whtBishopVect = pieces->getPiecesByFen('B');
	std::vector<Piece*>::const_iterator whtBishopItr = whtBishopVect.begin();

	const auto& blkQueenVect = pieces->getPiecesByFen('q');
	std::vector<Piece*>::const_iterator blkQueenItr = blkQueenVect.begin();

	const auto& whtQueenVect = pieces->getPiecesByFen('Q');
	std::vector<Piece*>::const_iterator whtQueenItr = whtQueenVect.begin();

	const auto& blkKingVect = pieces->getPiecesByFen('k');
	std::vector<Piece*>::const_iterator blkKingItr = blkKingVect.begin();

	const auto& whtKingVect = pieces->getPiecesByFen('K');
	std::vector<Piece*>::const_iterator whtKingItr = whtKingVect.begin();

	// Loop variables

	const auto& boardGrid = _gameScene->getBoard()->getBoardGrid();
	const std::string& fen = _fenManager->_fenPosition;
	std::string::const_iterator posItr = fen.begin();

	// Set position loop
	for (int row = 7; row >= 0; --row)
	{
		for (int col = 0; col <= boardGrid->at(row).size(); ++col)
		{
			if (posItr != fen.end())
			{
				switch (*posItr)
				{
				case (char)47:
					col = col + 8;
					break;
				case 'p':
					if (blkPawnItr != blkPawnVect.end())
					{
						(*blkPawnItr)->setSquare(&boardGrid->at(row).at(col));
						(*blkPawnItr)->getSquare()->getBoardIndex().first != 6 ? 
							(*blkPawnItr)->setFirstMove(false) : (*blkPawnItr)->setFirstMove(true);
						++blkPawnItr;
					}
					else
					{
						LOG(ERROR) << "No more pieces of type 'p' in vector!";
					}
					break;
				case 'P':
					if (whtPawnItr != whtPawnVect.end())
					{
						(*whtPawnItr)->setSquare(&boardGrid->at(row).at(col));
						(*whtPawnItr)->getSquare()->getBoardIndex().first != 1 ? 
							(*whtPawnItr)->setFirstMove(false) : (*whtPawnItr)->setFirstMove(true);
						++whtPawnItr;
					}
					else
					{
						LOG(ERROR) << "No more pieces of type 'P' in vector!";
					}
					break;
				case 'r':
					if (blkRookItr != blkRookVect.end())
					{
						(*blkRookItr)->setSquare(&boardGrid->at(row).at(col));
						++blkRookItr;
					}
					else
					{
						LOG(ERROR) << "No more pieces of type 'r' in vector!";
					}
					break;
				case 'R':
					if (whtRookItr != whtRookVect.end())
					{
						(*whtRookItr)->setSquare(&boardGrid->at(row).at(col));
						++whtRookItr;
					}
					else
					{
						LOG(ERROR) << "No more pieces of type 'R' in vector!";
					}
					break;
				case 'n':
					if (blkKnightItr != blkKnightVect.end())
					{
						(*blkKnightItr)->setSquare(&boardGrid->at(row).at(col));
						++blkKnightItr;
					}
					else
					{
						LOG(ERROR) << "No more pieces of type 'n' in vector!";
					}
					break;
				case 'N':
					if (whtKnightItr != whtKnightVect.end())
					{
						(*whtKnightItr)->setSquare(&boardGrid->at(row).at(col));
						++whtKnightItr;
					}
					else
					{
						LOG(ERROR) << "No more pieces of type 'N' in vector!";
					}
					break;
				case 'b':
					if (blkBishopItr != blkBishopVect.end())
					{
						(*blkBishopItr)->setSquare(&boardGrid->at(row).at(col));
						++blkBishopItr;
					}
					else
					{
						LOG(ERROR) << "No more pieces of type 'b' in vector!";
					}
					break;
				case 'B':
					if (whtBishopItr != whtBishopVect.end())
					{
						(*whtBishopItr)->setSquare(&boardGrid->at(row).at(col));
						++whtBishopItr;
					}
					else
					{
						LOG(ERROR) << "No more pieces of type 'B' in vector!";
					}
					break;
				case 'q':
					if (blkQueenItr != blkQueenVect.end())
					{
						(*blkQueenItr)->setSquare(&boardGrid->at(row).at(col));
						++blkQueenItr;
					}
					else
					{
						LOG(ERROR) << "No more pieces of type 'q' in vector!";
					}
					break;
				case 'Q':
					if (whtQueenItr != whtQueenVect.end())
					{
						(*whtQueenItr)->setSquare(&boardGrid->at(row).at(col));
						++whtQueenItr;
					}
					else
					{
						LOG(ERROR) << "No more pieces of type 'Q' in vector!";
					}
					break;
				case 'k':
					if (blkKingItr != blkKingVect.end())
					{
						(*blkKingItr)->setSquare(&boardGrid->at(row).at(col));

						++blkKingItr;
					}
					else
					{
						LOG(ERROR) << "No more pieces of type 'k' in vector!";
					}
					break;
				case 'K':
					if (whtKingItr != whtKingVect.end())
					{
						(*whtKingItr)->setSquare(&boardGrid->at(row).at(col));
						++whtKingItr;
					}
					else
					{
						LOG(ERROR) << "No more pieces of type 'K' in vector!";
					}
					break;
				case '1':
					if (col <= boardGrid->at(row).size())
					{
						col;
					}
					else
					{
						LOG(ERROR) << "Empty space exceeds size of board! Check your FEN.";
					}
					break;
				case '2':
					if (col + 1 <= boardGrid->at(row).size())
					{
						col = col + 1;
					}
					else
					{
						LOG(ERROR) << "Empty space exceeds size of board! Check your FEN.";
					}
					break;
				case '3':
					if (col + 2 <= boardGrid->at(row).size())
					{
						col = col + 2;
					}
					else
					{
						LOG(ERROR) << "Empty space exceeds size of board! Check your FEN.";
					}
					break;
				case '4':
					if (col + 3 <= boardGrid->at(row).size())
					{
						col = col + 3;
					}
					else
					{
						LOG(ERROR) << "Empty space exceeds size of board! Check your FEN.";
					}
					break;
				case '5':
					if (col + 4 <= boardGrid->at(row).size())
					{
						col = col + 4;
					}
					else
					{
						LOG(ERROR) << "Empty space exceeds size of board! Check your FEN.";
					}
					break;
				case '6':
					if (col + 5 <= boardGrid->at(row).size())
					{
						col = col + 5;
					}
					else
					{
						LOG(ERROR) << "Empty space exceeds size of board! Check your FEN.";
					}
					break;
				case '7':
					if (col + 6 <= boardGrid->at(row).size())
					{
						col = col + 6;
					}
					else
					{
						LOG(ERROR) << "Empty space exceeds size of board! Check your FEN.";
					}
					break;
				case '8':
					if (col + 7 <= boardGrid->at(row).size())
					{
						col = col + 7;
					}
					else
					{
						LOG(ERROR) << "Empty space exceeds size of board! Check your FEN.";
					}
					break;
				}
				++posItr;
			}
			else
			{
				break;
			}
		}
	}


	// Add the pieces to the render queue
	std::vector<std::pair<GameObject*, SDL_Texture*>> rendVect;
	PieceIterator pieceItr = pieces->createIterator();
	pieceItr.goToStart();

	for (int i = 0; i < pieceItr.getSize(); ++i)
	{
		pieceItr.goToIndex(i);
		rendVect.push_back(std::pair<GameObject*, SDL_Texture*>(&(*pieceItr.getCurrentPosition()), (*pieceItr.getCurrentPosition()).getGraphics()->getSdlTexture()));
	}

	ServiceLocator::getGraphics().addToRenderMap(2, rendVect);

}

void GameManager::setUpStockfish()
{
	_fishManager->newStockfishGame(_fenManager->createFishFen(_fenManager->createFenString(), false));
}

void GameManager::setTurn(bool color)
{
	_currentTurn = (int)color;
	_previousPlayer = _currentPlayer;

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

bool GameManager::checkForCheckmate()
{
	_fishManager->setUpStockfishPosition();
	std::string fishMove{_fishManager->calculateFishMove()};
	if (fishMove == "bestmove (none)\r")
	{
		return true;
	}
	else
	{
		return false;
	}
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
				if (p->isAlive() && p->getSquare()->getBoardIndex().second == 0 && (p->getSquare()->getBoardIndex().first == 0 || p->getSquare()->getBoardIndex().first == 7))
				{
					rookLeftFirstMove = p->getFirstMove();
					leftRook = p;
				}
				else if (p->isAlive() && p->getSquare()->getBoardIndex().second == 7 && (p->getSquare()->getBoardIndex().first == 0 || p->getSquare()->getBoardIndex().first == 7))
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
	if ((piece->isAlive() && piece->getSquare()->getBoardIndex().second == piece->getSquare()->getBoardIndex().second) &&
		((piece->getFenName() == 'P' && piece->getSquare()->getBoardIndex().first == 7) ||
			(piece->getFenName() == 'p' && piece->getSquare()->getBoardIndex().first == 0)))
	{
		if (_currentPlayer->getPlayerType() == Player::HUMAN)
		{
			_actionManager->promotePawn(piece, false);
		}
		else
		{
			_actionManager->promotePawn(piece, true);
		}
		char promotion{ piece->getFenName() };
		_fenManager->addPromoteToFenMove(promotion);
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

	// Reset FEN castle on capture undo
	if (piece->getPieceType() == Piece::ROOK && piece->getFirstMove())
	{
		if (piece->getSquare()->getBoardIndex().second == 0)
		{
			_fenManager->setCastleByColor(true, getTurn(), std::nullopt, true);
		}
		else if (piece->getSquare()->getBoardIndex().second == 7)
		{
			_fenManager->setCastleByColor(true, getTurn(), true, std::nullopt);
		}
	}

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

	// Create a FEN string for the start of this turn
	setCurrentFen();

	// Check for check. Set player check to false if player not in check. 
	// If this returns true, the player's check flag has already been set to true by the Highlight Manager,
	// so you do not need to set it here.
	if (_previousState != &InitGameState::getInstance() || _previousState != &EndGameState::getInstance())
	{
		if (!checkForCheck())
		{
			_currentPlayer->setCheck(false);
		}
		else
		{
			LOG(INFO) << _currentPlayer->getName() << " is in check! Be careful...";
			if (checkForCheckmate())
			{
				onCheckmate();
			}
		}
	}

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
	_fishManager->setUpStockfishPosition();
	std::thread fishThread(&GameManager::executeFishMove, this);
	fishThread.detach();
}

void GameManager::executeFishMove()
{

	// Calculate the best move and get the string pairs for that move
	std::string move{ _fishManager->calculateFishMove() };
	if (move == "bestmove (none)\r")
	{
		// checkmate
		onCheckmate();
		return;
	}
	else
	{
		std::pair<std::string, std::string> fishMove = _fishManager->parseBestMove(move);

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
		return;
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

void GameManager::onCheckmate()
{
	_victor = _previousPlayer;
	_victory = VictoryCondition::CHECKMATE;
	_gsm->changeState(this, "endGame");
}


