#include "ActionManager.h"
#include "easylogging++.h"
#include "GameManager.h"
#include "GameScene.h"
#include <conio.h>

ActionManager::ActionManager(GameManager* gm) :
	_gm(gm),
	_undoBuffer({new UndoValues(), new UndoValues()})
{}

void ActionManager::capturePiece(Piece* attacker, Piece* defender, bool passant, std::optional<Square*> passantSq)
{
	// Add the relevant objects to the undo buffer
	addToUndoBuffer(attacker, defender);
	// Unalive the defender
	defender->setAlive(false);
	// De-occupy the defender's square
	defender->getSquare()->setOccupied(false);
	
	if (!passant)
	{
		movePiece(attacker, defender->getSquare());
		return;
	}
	else if (passant && passantSq.has_value())
	{
		movePiece(attacker, passantSq.value());
		return;
	}
}

void ActionManager::captureEnPassant(Piece* attacker, Square* square)
{
	Square* defPos = nullptr;

	if (attacker->getFenName() == 'P')
	{
		defPos = &_gm->_gameScene->getBoard()->getBoardGrid()->at(square->getBoardIndex().first - 1).at(square->getBoardIndex().second);
	}
	else if (attacker->getFenName() == 'p')
	{
		defPos = &_gm->_gameScene->getBoard()->getBoardGrid()->at(square->getBoardIndex().first + 1).at(square->getBoardIndex().second);
	}

	if (defPos != nullptr && defPos->getOccupied())
	{
		capturePiece(attacker, defPos->getOccupant(), true, square);
		return;
	}
	else
	{
		LOG(ERROR) << "No piece in the available square to capture en passant!";
		return;
	}
}

void ActionManager::movePiece(Piece* piece, Square* target)
{

	// If there's nothing in the undo buffer (aka if this is a pure move with no capture), add moving piece to the undo buffer.
	if (!_undoBuffer.attacker && !_undoBuffer.defender)
	{
		addToUndoBuffer(piece);
	}

	// Set the source square before you move the piece so you can pass it to FEN
	Square& srcSq = *piece->getSquare();

	// Perform the actual move
	if (!target->getOccupied())
	{
		piece->getSquare()->setOccupied(false);
		piece->setSquare(target);
	}

	// Check if move is valid. If not, end the function.
	if (!testAction(piece))
	{
		return;
	}

	postMove(piece, &srcSq, target);

	return;

}

bool ActionManager::testAction(Piece* piece)
{
	bool valid = false;

	// Check if move would put the player's king in check
	if (_gm->checkForCheck())
	{
		LOG(INFO) << "This move would put your king in check! Illegal move.";
		// Revert the move if the move would put the king in check.
		if (!_undoBuffer.defender)
		{
			undoAction(piece, nullptr);
		}
		else
		{
			undoAction(piece, _gm->_gameScene->getPieceContainer()->getLastCapturedPiece());
		}
		_gm->notify("undoAction");
		return valid;
	}
	else
	{
		valid = true;
		return valid;
	}
}

void ActionManager::postFirstMove(Piece* piece, std::pair<int, int> moveDistance)
{
	// Set First Move to false for the piece
	piece->setFirstMove(false);

	// Set whether or not the piece can be captured en passant.
	if (piece->getPieceType() == Piece::PAWN && abs(moveDistance.first) == 2)
	{
		piece->setPassantable(true);
		_gm->notify(piece, "piecePassant");
	}

	// Set the FEN castling modifier for kings and rooks
	if (piece->getPieceType() == Piece::KING)
	{
		// Set castling to this side to false because the king moved
		_gm->_fenManager->setCastleByColor(false, _gm->getTurn(), false, false);
	}
	else if (piece->getPieceType() == Piece::ROOK)
	{
		if (piece->getSquare()->getBoardIndex().second == 0)
		{
			// Set queenside castling to false because the queenside rook just moved.
			_gm->_fenManager->setCastleByColor(true, _gm->getTurn(), std::nullopt, false);
		}
		else if (piece->getSquare()->getBoardIndex().second == 7)
		{
			// Set kingside castling to false because the kingside rook just moved.
			_gm->_fenManager->setCastleByColor(true, _gm->getTurn(), false, std::nullopt);
		}
	}
}

void ActionManager::promotePawn(Piece* piece)
{
	// TODO: Handle in the console for now, later I'll make a GUI for it
	
	bool run = true;
	char input = NULL;

	// Render map vectors for updating the texture if necessary
	std::vector<std::pair<GameObject*, SDL_Texture*>> vect;
	std::pair<GameObject*, SDL_Texture*> pair;
	pair.first = piece;
	pair.second = piece->getGraphics()->getSdlTexture();
	vect.push_back(pair);

	while (run = true)
	{
		system("cls");
		try
		{
			std::cout << "Do you want to promote the pawn on " << piece->getSquare()->getName() << "?\nY/n\n";
			input = _getch();
			if (input != 'Y' && input != 'y' && input != 'n' && input != 'N')
			{
				throw input;
			}
			else if (input == 'Y' || input == 'y')
			{
				ServiceLocator::getGraphics().removeFromRenderMap(vect);
				try
				{
				// Select piece to turn into
				std::cout << "Select which figure to promote to:\n1. Queen\n2. Rook\n3. Bishop\n4. Knight\n";
				char choice = _getch();
				
					switch (choice)
					{
					case '1':
						piece->changeType(Piece::Figure::QUEEN);
						run = false;
						break;
					case '2':
						piece->changeType(Piece::Figure::ROOK);
						run = false;
						break;
					case '3':
						piece->changeType(Piece::Figure::BISHOP);
						run = false;
						break;
					case '4':
						piece->changeType(Piece::Figure::KNIGHT);
						run = false;
						break;
					default:
						throw choice;
						continue;
					}
				}
				catch (char e)
				{
					LOG(ERROR) << "Invalid input: " << e;
					ServiceLocator::getGraphics().addToRenderMap(2, vect);
					continue;
				}
				vect.clear();
				pair.first = piece;
				pair.second = piece->getGraphics()->getSdlTexture();
				vect.push_back(pair);
				ServiceLocator::getGraphics().addToRenderMap(2, vect);
			}
			else if (input == 'N' || input == 'n')
			{
				run = false;
				break;
			}
		}
		catch (char c)
		{
			LOG(ERROR) << "Invalid input: " << c;
			continue;
		}

		SDL_RaiseWindow(ServiceLocator::getGraphics().getWindow()->getWindow());
		run = false;	
		break;
	}

	vect.clear();

}

void ActionManager::castleKing(Piece* king, Square* square)
{
	// Find the nearest rook to the selected square.
	Piece* rook = nullptr;
	if (king->getPieceColor() == Piece::BLACK)
	{
		// Is the square on the black left side?
		if (square->getBoardIndex().first == 7 && square->getBoardIndex().second == 2)
		{
			rook = _gm->_gameScene->getBoard()->getBoardGrid()->at(7).at(0).getOccupant();
			// Move the rook to the appropriate place.
			rook->getSquare()->setOccupied(false);
			rook->setSquare(&_gm->_gameScene->getBoard()->getBoardGrid()->at(7).at(3));	
		}
		// ...or is it on the black right side?
		else if (square->getBoardIndex().first == 7 && square->getBoardIndex().second == 6)
		{
			rook = _gm->_gameScene->getBoard()->getBoardGrid()->at(7).at(7).getOccupant();
			// Move the rook to the appropriate place.
			rook->getSquare()->setOccupied(false);
			rook->setSquare(&_gm->_gameScene->getBoard()->getBoardGrid()->at(7).at(5));
		}
	}
	else if (king->getPieceColor() == Piece::WHITE)
	{
		// ...or is it on the white left side?
		if (square->getBoardIndex().first == 0 && square->getBoardIndex().second == 2)
		{
			rook = _gm->_gameScene->getBoard()->getBoardGrid()->at(0).at(0).getOccupant();
			// Move the rook to the appropriate place.
			rook->getSquare()->setOccupied(false);
			rook->setSquare(&_gm->_gameScene->getBoard()->getBoardGrid()->at(0).at(3));
		}
		// ...or is it on the white right side?
		else if (square->getBoardIndex().first == 0 && square->getBoardIndex().second == 6)
		{
			rook = _gm->_gameScene->getBoard()->getBoardGrid()->at(0).at(7).getOccupant();
			// Move the rook to the appropriate place.
			rook->getSquare()->setOccupied(false);
			rook->setSquare(&_gm->_gameScene->getBoard()->getBoardGrid()->at(0).at(5));
		}
	}

	// Move the king.
	movePiece(king, square);

}

void ActionManager::postMove(Piece* piece, Square* srcSq, Square* tarSq)
{

	// Get the distance the piece moved
	std::pair<int, int> moveDistance = { 0, 0 };
	moveDistance = { tarSq->getBoardIndex().first - srcSq->getBoardIndex().first,
					tarSq->getBoardIndex().second - srcSq->getBoardIndex().second };

	// If the piece was passantable before this move, it should no longer be passantable after the move.
	if (piece->getPassantable() == true)
	{
		piece->setPassantable(false);
	}

	// If this was the piece's first move, set first move to false for future moves.
	if (piece->getFirstMove())
	{
		postFirstMove(piece, moveDistance);
	}

	// Update the FEN Manager with the move string
	_gm->_fenManager->setFenMove(srcSq->getName(), tarSq->getName());

	// If this move involved a capture (which is knowable from looking at the Undo Buffer), notify that we should reset the half move counter.
	if (_undoBuffer.defender)
	{
		_gm->notify("halfMoveReset");
	}

	// Notify the GameManager that the position has changed.
	_gm->notify(piece, "pieceMove");

}

void ActionManager::addToUndoBuffer(Piece* attacker, Piece* defender)
{
	if (attacker)
	{
		_undoBuffer.attacker = new UndoValues;
		_undoBuffer.attacker->alive = attacker->isAlive();
		_undoBuffer.attacker->firstMove = attacker->getFirstMove();
		_undoBuffer.attacker->passantable = attacker->getPassantable();
		_undoBuffer.attacker->square = attacker->getSquare();
	}
	if (defender)
	{
		_undoBuffer.defender = new UndoValues;
		_undoBuffer.defender->alive = defender->isAlive();
		_undoBuffer.defender->firstMove = defender->getFirstMove();
		_undoBuffer.defender->passantable = defender->getPassantable();
		_undoBuffer.defender->square = defender->getSquare();
	}

	return;
}

ActionManager::UndoBuffer ActionManager::getUndoBuffer()
{
	return _undoBuffer;
}

void ActionManager::clearUndoBuffer()
{
	_undoBuffer = { nullptr, nullptr};
}

void ActionManager::undoAction(Piece* attacker, Piece* defender)
{
	if (attacker != nullptr && _undoBuffer.attacker != nullptr)
	{
		attacker->setFirstMove(_undoBuffer.attacker->firstMove);
		attacker->setAlive(_undoBuffer.attacker->alive);
		attacker->getSquare()->setOccupied(false);
		attacker->setSquare(_undoBuffer.attacker->square);
		attacker->setPassantable(_undoBuffer.attacker->passantable);
	}
	if (defender != nullptr && _undoBuffer.defender != nullptr)
	{
		defender->setFirstMove(_undoBuffer.defender->firstMove);
		defender->setAlive(_undoBuffer.defender->alive);
		defender->getSquare()->setOccupied(false);
		defender->setSquare(_undoBuffer.defender->square);
		defender->setPassantable(_undoBuffer.defender->passantable);
	}
	
}