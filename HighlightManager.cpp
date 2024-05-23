#include "GameScene.h"
#include "HighlightManager.h"
#include "easylogging++.h";

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

template<typename Func>
void HighlightManager::moveOptions(Square* square, Rules::RulePackage rules, Func f)
{
	std::vector<std::vector<Square>>* grid = _gm->_gameScene->getBoard()->getBoardGrid();
	std::pair<int, int> squareIndex = square->getBoardIndex();

	for (int iRow = 0; iRow <= rules.moveRules.row; ++iRow)
	{
		for (int iCol = 0; iCol <= rules.moveRules.column; ++iCol)
		{
			if (((squareIndex.first + iRow <= 7) && (squareIndex.first + iRow >= 0))
				&& ((squareIndex.second + iCol <= 7) && (squareIndex.second + iCol >= 0)))
			{
				f(iRow, iCol, grid, squareIndex);
			}
		}
	}
}

template<typename F1, typename F2>
void HighlightManager::captureOptionLoop(Square* square, Rules::RulePackage rules, F1 f1, F2 f2)
{
	std::vector<std::vector<Square>>* grid = _gm->_gameScene->getBoard()->getBoardGrid();
	std::pair<int, int> squareIndex = square->getBoardIndex();

	for (int iRow = 1; iRow <= rules.captureRules.row; ++iRow)
	{
		// Positive column iterator
		for (int iCol = 1; iCol <= rules.captureRules.column; ++iCol)
		{
			if ((squareIndex.first + iRow <= 7) && (squareIndex.first + iRow >= 0))
			{
				if ((squareIndex.second + iCol <= 7) && (squareIndex.second + iCol >= 0))
				{
					f1(iRow, iCol, grid, squareIndex);
				}
				if ((squareIndex.second - iCol <= 7) && (squareIndex.second - iCol >= 0))
				{
					f2(iRow, iCol, grid, squareIndex);
				}
			}
		}
	}
}

Rules::RulePackage HighlightManager::getPieceRules(Piece* piece)
{
	Rules::RulePackage rules = _gm->getRules()->getRulesPackage(piece);

	return rules;
}

void HighlightManager::highlightActionOptions(Square* square)
{

	Rules::RulePackage rules = getPieceRules(square->getOccupant());

	// Move Highlighting
	// *************************

	// Compute orthogonal moves
	if (rules.moveRules.orthoMove == true)
	{
		highlightOrthoMoveOptions(square, rules);
	}

	// Capture Highlighting
	// *************************

	// Compute orthogonal captures
	if (rules.captureRules.orthoCapture == true)
	{
		highlightOrthoCaptureOptions(square, rules);
	}

	// Compute diagonal captures
	if (rules.captureRules.diagCapture == true)
	{
		highlightDiagCaptureOptions(square, rules);
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

void HighlightManager::highlightOrthoMoveOptions(Square* square, Rules::RulePackage rules)
{

	orthoPosRowOptions(square, rules);
	orthoNegRowOptions(square, rules);
	orthoPosColOptions(square, rules);
	orthoNegColOptions(square, rules);

}

void HighlightManager::orthoPosRowOptions(Square* square, Rules::RulePackage rules)
{
	std::vector<std::vector<Square>>* grid = _gm->_gameScene->getBoard()->getBoardGrid();
	std::pair<int, int> squareIndex = square->getBoardIndex();

	// If not a black pawn...
	if (square->getOccupant()->getFenName() != 'p')
	{
		// Evaluate upward
		for (int iRow = 1; iRow <= rules.moveRules.row; ++iRow)
		{
			// Break if the row to evaluate goes above the size of the board
			if (squareIndex.first + iRow >= grid->size() - 1)
			{
				break;
			}
			// Evaluate upward movement
			if (!grid->at(squareIndex.first + iRow).at(squareIndex.second).getOccupied())
			{
				grid->at(squareIndex.first + iRow).at(squareIndex.second).setOverlayType(Square::MOVE);
			}
			// Stop adding movement overlays once you encounter another piece
			if (grid->at(squareIndex.first + iRow).at(squareIndex.second).getOccupied())
			{
				break;
			}
		}
	}
}

void HighlightManager::orthoNegRowOptions(Square* square, Rules::RulePackage rules)
{
	std::vector<std::vector<Square>>* grid = _gm->_gameScene->getBoard()->getBoardGrid();
	std::pair<int, int> squareIndex = square->getBoardIndex();

	// If not a white pawn...
	if (square->getOccupant()->getFenName() != 'P')
		// Evaluate downward
	{
		for (int iRow = -1; iRow >= rules.moveRules.row * -1; --iRow)
		{
			// Break if the row to evaluate goes above the size of the board
			if (squareIndex.first + iRow < 0)
			{
				break;
			}
			if (!grid->at(squareIndex.first + iRow).at(squareIndex.second).getOccupied())
			{
				grid->at(squareIndex.first + iRow).at(squareIndex.second).setOverlayType(Square::MOVE);
			}
		}
	}
}

void HighlightManager::orthoPosColOptions(Square* square, Rules::RulePackage rules)
{}

void HighlightManager::orthoNegColOptions(Square* square, Rules::RulePackage rules)
{}

void HighlightManager::highlightOrthoCaptureOptions(Square* square, Rules::RulePackage rules)
{
	//captureOptionLoop(square, rules, [this](int iRow, int iCol, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
	//	{
	//		// If the squares within the piece's capture range straight up and down are occupied, put up the take overlay
	//		if (grid->at(squareIndex.first + iRow).at(squareIndex.second).getOccupied() &&
	//			grid->at(squareIndex.first + iRow).at(squareIndex.second).getOccupant()->getPieceColor() != _gm->_currentTurn)
	//		{
	//			grid->at(squareIndex.first + iRow).at(squareIndex.second).setOverlayType(Square::TAKE);
	//		}
	//		/*if (grid->at(squareIndex.first - iRow).at(squareIndex.second).getOccupied() &&
	//			grid->at(squareIndex.first - iRow).at(squareIndex.second).getOccupant()->getPieceColor() != _gm->_currentTurn)
	//		{
	//			grid->at(squareIndex.first - iRow).at(squareIndex.second).setOverlayType(Square::TAKE);
	//		}*/
	//	},
	//	[this](int iRow, int iCol, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
	//	{
	//		// If the squares within the piece's capture range straight left and right are occupied, put up the take overlay
	//		if (grid->at(squareIndex.first).at(squareIndex.second + iCol).getOccupied() &&
	//			grid->at(squareIndex.first).at(squareIndex.second + iCol).getOccupant()->getPieceColor() != _gm->_currentTurn)
	//		{
	//			grid->at(squareIndex.first).at(squareIndex.second + iCol).setOverlayType(Square::TAKE);
	//		}
	//		/*if (grid->at(squareIndex.first).at(squareIndex.second - iCol).getOccupied() &&
	//			grid->at(squareIndex.first).at(squareIndex.second - iCol).getOccupant()->getPieceColor() != _gm->_currentTurn)
	//		{
	//			grid->at(squareIndex.first).at(squareIndex.second - iCol).setOverlayType(Square::TAKE);
	//		}*/
	//	});
}

void HighlightManager::highlightDiagCaptureOptions(Square* square, Rules::RulePackage rules)
{

	captureOptionLoop(square, rules, [this](int iRow, int iCol, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
		{
			// If the square up one and right one from the selected square is occupied by an opponent's piece, put on the Take overlay.
			if (grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupied() &&
				grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupant()->getPieceColor() != _gm->_currentTurn)
			{
				grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).setOverlayType(Square::TAKE);
			}
		},
		[this](int iRow, int iCol, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
		{
			// Do the same thing, but to the left (negative on the board index)
			if (grid->at(squareIndex.first + iRow).at(squareIndex.second - iCol).getOccupied() &&
				grid->at(squareIndex.first + iRow).at(squareIndex.second - iCol).getOccupant()->getPieceColor() != _gm->_currentTurn)
			{
				grid->at(squareIndex.first + iRow).at(squareIndex.second - iCol).setOverlayType(Square::TAKE);
			}
		});

}