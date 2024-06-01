#include "ActionManager.h"
#include "easylogging++.h"
#include "GameManager.h"
#include "GameScene.h"
#include "HighlightManager.h"
#include "SelectionManager.h"
#include "PieceIterator.h"

SelectionManager::SelectionManager(GameManager* gm) :
	_gm(gm)
{}


template<typename Func>
void SelectionManager::boardGridLoop(Func f)
{
	for (int row = 0; row < _gm->_gameScene->getBoard()->getBoardGrid()->size(); ++row)
	{
		for (int col = 0; col < _gm->_gameScene->getBoard()->getBoardGrid()->at(row).size(); ++col)
		{
			f(row, col);
		}
	}
}

void SelectionManager::handleClick()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	SDL_Point mousePos = { x, y };
	SDL_Rect boardDim = _gm->_gameScene->getBoard()->getBoardDimensions();

	if (SDL_PointInRect(&mousePos, &boardDim))
	{
		handleClickOnBoard(x, y);
	}
	else
	{
		deselectPieces();
	}
}

void SelectionManager::handleClickOnBoard(int x, int y)
{
	// Set the point to where the mouse was when clicked
	SDL_Point clickPos = { x, y };
	

	// Determine whether the point intersects with any squares.
	boardGridLoop([this, clickPos](int row, int col)
		{
			// Declare variable to simplify code
			auto& square = this->_gm->_gameScene->getBoard()->getBoardGrid()->at(row).at(col);

			if (SDL_PointInRect(&clickPos, square.getDimensions()))
			{
				// Send the clicked square's name to the Debug log
				LOG(DEBUG) << "Square " << square.getName() << " clicked!";
				// If square is occupied...
				if (square.getOccupied() && square.getOccupant() != nullptr)
				{
					handleClickOnPiece(square.getOccupant());
				}
				else
				{
					handleClickOnEmptySquare(&square);
				}
			}
		});

}

void SelectionManager::handleClickOnEmptySquare(Square* square)
{
	// If the square has no overlay, therefore cannot be moved to or captured from, deselect all pieces
	switch (square->getOverlayType())
	{
	case Square::NONE:
		deselectPieces();
		break;
	case Square::MOVE:
		// move logic
		_gm->_actionManager->movePiece(_gm->_selectedPiece, square);
		// End turn here after moving the piece? Or call a different function?
		break;
	case Square::TAKE:
		// Used primarily for en passant captures
		_gm->_actionManager->captureEnPassant(_gm->_selectedPiece, square);
		deselectPieces();
		break;
	case Square::CASTLE:
		// Castle the king
		_gm->_actionManager->castleKing(_gm->_selectedPiece, square);
		break;
	default:
		deselectPieces();
		break;
	}
}

void SelectionManager::handleClickOnPiece(Piece* piece)
{
	// If the piece is alive and belongs to the player whose turn it is, select the piece.
	// Otherwise, deselect all pieces
	if (piece->isAlive() && piece->getPieceColor() == _gm->getTurn())
	{
		selectPiece(piece);
	}
	// Handle what happens if you click on an opposing piece
	else if (piece->isAlive() && piece->getPieceColor() != _gm->getTurn())
	{
		// If the square has a Take overlay (aka the piece on it can be taken)
		if (piece->getSquare()->getOverlayType() == Square::TAKE)
		{
			// Capture the piece clicked on using the currently selected piece
			_gm->_actionManager->capturePiece(_gm->_selectedPiece, piece);
		}
		else
		{
			// Deselect all pieces if you can't take the piece
			deselectPieces();
		}
	}
}

void SelectionManager::selectPiece(Piece* piece)
{
	// Deselect all pieces but this one, if it is already selected.
	deselectPieces(piece);

	// If the supplied piece is already selected, deselect it. If it's not selected, select it.
	if (piece->getSelected())
	{
		piece->setSelected(false);
		_gm->_selectedPiece = nullptr;
		_gm->_highlightManager->removeActionHighlight();

	}
	else
	{
		piece->setSelected(true);
		_gm->_selectedPiece = piece;
		_gm->_highlightManager->highlightActionOptions(piece->getSquare());
	}

}

void SelectionManager::deselectPieces(Piece* exception)
{
	PieceIterator pieceItr = _gm->_gameScene->getPieceContainer()->createIterator(); 

	if (exception != nullptr)
	{
		for (pieceItr; !pieceItr.isDone(); pieceItr.goForward(1))
		{
			if ((*pieceItr.getCurrentPosition()).getSelected() && (*pieceItr.getCurrentPosition()).getSquare() != exception->getSquare())
			{
				(*pieceItr.getCurrentPosition()).setSelected(false);
				LOG(DEBUG) << "Piece " << (*pieceItr.getCurrentPosition()).getFenName() << " has been deselected!";
				_gm->_selectedPiece = nullptr;
			}
		}
	}
	else
	{
		for (pieceItr; !pieceItr.isDone(); pieceItr.goForward(1))
		{
			if ((*pieceItr.getCurrentPosition()).getSelected())
			{
				(*pieceItr.getCurrentPosition()).setSelected(false);
				LOG(DEBUG) << "Piece " << (*pieceItr.getCurrentPosition()).getFenName() << " has been deselected!";
				_gm->_selectedPiece = nullptr;
			}
		}
	}
	_gm->_highlightManager->removeActionHighlight();

}