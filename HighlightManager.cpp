#include "HighlightManager.h"
#include "GameManager.h"
#include "GameScene.h"

HighlightManager::HighlightManager(GameManager* gm) :
	_gm(gm)
{}


template<typename Func>
void HighlightManager::boardGridLoop(Func f)
{
	for (int row = 0; row < _gm->_gameScene->getBoard()->getBoardGrid()->size(); ++row)
	{
		for (int col = 0; col < _gm->_gameScene->getBoard()->getBoardGrid()->at(row).size(); ++col)
		{
			f(row, col);
		}
	}
}

void HighlightManager::highlightActionOptions(Square* square)
{
	// Set local variables
	Rules::RulePackage rules;
	std::vector<std::vector<Square>>* grid = _gm->_gameScene->getBoard()->getBoardGrid();
	std::pair<int, int> squareIndex = square->getBoardIndex();

	// Get the type of piece on the square and determine which rule evaluation set to use on it.
	switch (square->getOccupant()->getFenName())
	{
	case 'P':
		rules = _gm->_rules.get()->getWhtPawnRules(square->getOccupant());
		break;
	}

	// Move Highlighting
	// *************************

	// Compute orthogonal moves
	if (rules.moveRules.orthoMove == true)
	{
		// Compute move distance
		for (int iRow = 0; iRow <= rules.moveRules.row; ++iRow)
		{
			for (int iCol = 0; iCol <= rules.moveRules.column; ++iCol)
			{
				if (((squareIndex.first + iRow <= 7) && (squareIndex.first + iRow >= 0))
					&& ((squareIndex.second + iCol <= 7) && (squareIndex.second + iCol >= 0)))
				{
					// If the square within the move distance is not occupied, set the move overlay for that square
					if (!grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupied())
					{
						grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).setOverlayType(Square::MOVE);
					}
				}
			}
		}
	}

	// Capture Highlighting
	// *************************

	// Compute orthogonal captures

	// Compute diagonal captures
	if (rules.captureRules.diagCapture == true)
	{
		for (int iRow = 1; iRow <= rules.captureRules.row; ++iRow)
		{
			// Positive column iterator
			for (int iCol = 1; iCol <= rules.captureRules.column; ++iCol)
			{
				if ((squareIndex.first + iRow <= 7) && (squareIndex.first + iRow >= 0))
				{
					if ((squareIndex.second + iCol <= 7) && (squareIndex.second + iCol >= 0))
					{
						// If the square up one and right one from the selected square is occupied by an opponent's piece, put on the Take overlay.
						if (grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupied() &&
							grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupant()->getPieceColor() != _gm->_currentTurn)
						{
							grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).setOverlayType(Square::TAKE);
						}
					}
					if ((squareIndex.second - iCol <= 7) && (squareIndex.second - iCol >= 0))
					{
						// Do the same thing, but to the left (negative on the board index)
						if (grid->at(squareIndex.first + iRow).at(squareIndex.second - iCol).getOccupied() &&
							grid->at(squareIndex.first + iRow).at(squareIndex.second - iCol).getOccupant()->getPieceColor() != _gm->_currentTurn)
						{
							grid->at(squareIndex.first + iRow).at(squareIndex.second - iCol).setOverlayType(Square::TAKE);
						}
					}
				}
			}
		}
	}

}

void HighlightManager::removeActionHighlight()
{
	boardGridLoop([this](int row, int col) {
		// Declare variable to simplify code
		auto& square = _gm->_gameScene->getBoard()->getBoardGrid()->at(row).at(col);
		if (square.getOverlayType() != Square::NONE)
		{
			square.setOverlayType(Square::NONE);
		}
		});
}