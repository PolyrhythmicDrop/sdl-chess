#include "GameScene.h"
#include "HighlightManager.h"
#include "easylogging++.h"

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

template<typename M, typename T>
void HighlightManager::diagMoveOptions(Square* square, Rules::RulePackage rules, M m, T t)
{
	std::vector<std::vector<Square>>* grid = _gm->_gameScene->getBoard()->getBoardGrid();
	std::pair<int, int> squareIndex = square->getBoardIndex();

	bool finished = false;

	// Up-right
	for (int iRow = 1; iRow <= rules.moveRules.row && !finished; ++iRow)
	{
		for (int iCol = 1; iCol <= rules.moveRules.column && !finished; ++iCol)
		{
			// Break if we exceed the size of the board
			if (squareIndex.first + iRow >= grid->size() || squareIndex.second + iCol >= grid->size())
			{
				finished = true;
				break;
			}
			if (!grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupied())
			{
				m(iRow, iCol, grid, squareIndex);
				++iRow;
			}
			else if (grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupied() &&
				grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupant()->getPieceColor() != _gm->_currentTurn)
			{
				t(iRow, iCol, grid, squareIndex);
				finished = true;
				break;
			}
			else
			{
				finished = true;
				break;
			}
		}
	}

	finished = false;
	
	// Down-right
	for (int iRow = -1; iRow >= rules.moveRules.row * -1 && !finished; --iRow)
	{
		for (int iCol = 1; iCol <= rules.moveRules.column && !finished; ++iCol)
		{
			// Break if we exceed the size of the board
			if (squareIndex.first + iRow >= grid->size() || squareIndex.second + iCol >= grid->size())
			{
				finished = true;
				break;
			}
			if (!grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupied())
			{
				m(iRow, iCol, grid, squareIndex);
				--iRow;
			}
			else if (grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupied() &&
				grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupant()->getPieceColor() != _gm->_currentTurn)
			{
				t(iRow, iCol, grid, squareIndex);
				finished = true;
				break;
			}
			else
			{
				finished = true;
				break;
			}
		}
	}

	finished = false;
	
	// Up-left
	for (int iRow = 1; iRow <= rules.moveRules.row && !finished; ++iRow)
	{
		for (int iCol = -1; iCol >= rules.moveRules.column * -1 && !finished; --iCol)
		{
			// Break if we exceed the size of the board
			if (squareIndex.first + iRow >= grid->size() || squareIndex.second + iCol >= grid->size())
			{
				finished = true;
				break;
			}
			if (!grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupied())
			{
				m(iRow, iCol, grid, squareIndex);
				++iRow;
			}
			else if (grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupied() &&
				grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupant()->getPieceColor() != _gm->_currentTurn)
			{
				t(iRow, iCol, grid, squareIndex);
				finished = true;
				break;
			}
			else
			{
				finished = true;
				break;
			}
		}
	}

	finished = false;
	
	// Down-left
	for (int iRow = -1; iRow >= rules.moveRules.row * -1 && !finished; --iRow)
	{
		for (int iCol = -1; iCol >= rules.moveRules.column * -1 && !finished; --iCol)
		{
			// Break if we exceed the size of the board
			if (squareIndex.first + iRow >= grid->size() || squareIndex.second + iCol >= grid->size())
			{
				finished = true;
				break;
			}
			if (!grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupied())
			{
				m(iRow, iCol, grid, squareIndex);
				--iRow;
			}
			else if (grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupied() &&
				grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupant()->getPieceColor() != _gm->_currentTurn)
			{
				t(iRow, iCol, grid, squareIndex);
				finished = true;
				break;
			}
			else
			{
				finished = true;
				break;
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
	std::vector<std::vector<Square>>* grid = _gm->_gameScene->getBoard()->getBoardGrid();
	std::pair<int, int> squareIndex = square->getBoardIndex();

	Rules::RulePackage rules = getPieceRules(square->getOccupant());

	// Move Highlighting
	// *************************

	// Compute orthogonal moves
	if (rules.moveRules.orthoMove == true)
	{
		highlightOrthoMoveOptions(square, rules, grid, squareIndex);
	}

	// Compute diagonal moves
	if (rules.moveRules.diagMove == true)
	{
		highlightDiagMoveOptions(square, rules);
	}

	// Capture Highlighting
	// *************************

	// Compute orthogonal captures
	if (rules.captureRules.orthoCapture == true)
	{
		highlightOrthoCaptureOptions(square, rules, grid, squareIndex);
	}

	// Compute diagonal captures
	/*if (rules.captureRules.diagCapture == true)
	{
		highlightDiagCaptureOptions(square, rules);
	}*/

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

void HighlightManager::highlightOrthoMoveOptions(Square* square, Rules::RulePackage rules, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
{

	orthoMovePosRowOptions(square, rules, grid, squareIndex);
	orthoMoveNegRowOptions(square, rules, grid, squareIndex);

	orthoMovePosColOptions(square, rules, grid, squareIndex);
	orthoMoveNegColOptions(square, rules, grid, squareIndex);

}

void HighlightManager::orthoMovePosRowOptions(Square* square, Rules::RulePackage rules, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
{

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
			else if (grid->at(squareIndex.first + iRow).at(squareIndex.second).getOccupied())
			{
				break;
			}
		}
	}
}

void HighlightManager::orthoMoveNegRowOptions(Square* square, Rules::RulePackage rules, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
{

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
			// Stop adding movement overlays once you encounter another piece
			else if (grid->at(squareIndex.first + iRow).at(squareIndex.second).getOccupied())
			{
				break;
			}
		}
	}
}

void HighlightManager::orthoMovePosColOptions(Square* square, Rules::RulePackage rules, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
{
	for (int iCol = 1; iCol <= rules.moveRules.column; ++iCol)
	{
		// Break if the row to evaluate goes above the size of the board
		if (squareIndex.second + iCol >= grid->size())
		{
			break;
		}
		// Evaluate upward movement
		if (!grid->at(squareIndex.first).at(squareIndex.second + iCol).getOccupied())
		{
			grid->at(squareIndex.first).at(squareIndex.second + iCol).setOverlayType(Square::MOVE);
		}
		// Stop adding movement overlays once you encounter another piece
		else if (grid->at(squareIndex.first).at(squareIndex.second + iCol).getOccupied())
		{
			break;
		}
	}


}

void HighlightManager::orthoMoveNegColOptions(Square* square, Rules::RulePackage rules, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
{
	for (int iCol = -1; iCol >= rules.moveRules.column * -1; --iCol)
	{
		// Break if the row to evaluate goes above the size of the board
		if (squareIndex.second + iCol < 0)
		{
			break;
		}
		if (!grid->at(squareIndex.first).at(squareIndex.second + iCol).getOccupied())
		{
			grid->at(squareIndex.first).at(squareIndex.second + iCol).setOverlayType(Square::MOVE);
		}
		// Stop adding movement overlays once you encounter another piece
		else if (grid->at(squareIndex.first).at(squareIndex.second + iCol).getOccupied())
		{
			break;
		}
	}
}

void HighlightManager::highlightDiagMoveOptions(Square* square, Rules::RulePackage rules)
{
	
	diagMoveOptions(square, rules, [this](int iRow, int iCol, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
		{
			grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).setOverlayType(Square::MOVE);
		},
		[this](int iRow, int iCol, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex) 
		{
			grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).setOverlayType(Square::TAKE);
		});

}

void HighlightManager::diagMovePosRowOptions(Square* square, Rules::RulePackage rules, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
{
	bool finished = false;

	// Evaluate upward
	for (int iRow = 1; iRow <= rules.moveRules.row && !finished; ++iRow)
	{
		for (int iCol = 1; iCol <= rules.moveRules.column && !finished; ++iCol)
		{
			// Break if we exceed the size of the board
			if (squareIndex.first + iRow >= grid->size() || squareIndex.second + iCol >= grid->size())
			{
				finished = true;
				break;
			}
			if (!grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupied())
			{
				grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).setOverlayType(Square::MOVE);
				++iRow;
			}
			else if (grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupied() &&
				grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupant()->getPieceColor() != _gm->_currentTurn)
			{
				grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).setOverlayType(Square::TAKE);
				finished = true;
				break;
				break;
			}
			else
			{
				finished = true;
				break;
			}
		}
	}

}

void HighlightManager::diagMoveNegRowOptions(Square* square, Rules::RulePackage rules, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
{
	bool finished = false;

	// Evaluate upward
	for (int iRow = -1; iRow >= rules.moveRules.row * -1 && !finished; --iRow)
	{
		for (int iCol = 1; iCol <= rules.moveRules.column && !finished; ++iCol)
		{
			// Break if we exceed the size of the board
			if (squareIndex.first + iRow >= grid->size() || squareIndex.second + iCol >= grid->size())
			{
				finished = true;
				break;
			}
			if (!grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupied())
			{
				grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).setOverlayType(Square::MOVE);
				--iRow;
			}
			else if (grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupied() && grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupant()->getPieceColor() != _gm->_currentTurn)
			{
				grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).setOverlayType(Square::TAKE);
				finished = true;
				break;
			}
			else
			{
				finished = true;
				break;
			}
		}
	}
}

void HighlightManager::diagMovePosColOptions(Square* square, Rules::RulePackage rules, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
{
	bool finished = false;

	for (int iRow = 1; iRow <= rules.moveRules.row && !finished; ++iRow)
	{
		for (int iCol = -1; iCol >= rules.moveRules.column * -1 && !finished; --iCol)
		{
			// Break if we exceed the size of the board
			if (squareIndex.first + iRow >= grid->size() || squareIndex.second + iCol >= grid->size())
			{
				finished = true;
				break;
			}
			if (!grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupied())
			{
				grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).setOverlayType(Square::MOVE);
				++iRow;
			}
			else if (grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupied() && grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupant()->getPieceColor() != _gm->_currentTurn)
			{
				grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).setOverlayType(Square::TAKE);
				finished = true;
				break;
			}
			else
			{
				finished = true;
				break;
			}
		}
	}
}

void HighlightManager::diagMoveNegColOptions(Square* square, Rules::RulePackage rules, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
{
	bool finished = false;

	for (int iRow = -1; iRow >= rules.moveRules.row * -1 && !finished; --iRow)
	{
		for (int iCol = -1; iCol >= rules.moveRules.column * -1 && !finished; --iCol)
		{
			// Break if we exceed the size of the board
			if (squareIndex.second + iCol >= grid->size() || squareIndex.first + iRow >= grid->size())
			{
				finished = true;
				break;
			}
			if (!grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupied())
			{
				grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).setOverlayType(Square::MOVE);
				--iRow;
			}
			else if (grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupied() && grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupant()->getPieceColor() != _gm->_currentTurn)
			{
				grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).setOverlayType(Square::TAKE);
				finished = true;
				break;
			}
			else
			{
				finished = true;
				break;
			}
		}
	}
}


void HighlightManager::highlightOrthoCaptureOptions(Square* square, Rules::RulePackage rules, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
{
	orthoCapturePosRowOptions(square, rules, grid, squareIndex);
	orthoCaptureNegRowOptions(square, rules, grid, squareIndex);

	orthoCapturePosColOptions(square, rules, grid, squareIndex);
	orthoCaptureNegColOptions(square, rules, grid, squareIndex);

}

void HighlightManager::orthoCapturePosRowOptions(Square* square, Rules::RulePackage rules, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
{
	// Evaluate upward
	for (int iRow = 1; iRow <= rules.captureRules.row; ++iRow)
	{
		// Break if the row to evaluate goes above the size of the board
		if (squareIndex.first + iRow >= grid->size())
		{
			break;
		}
		// Evaluate upward captures
		if (grid->at(squareIndex.first + iRow).at(squareIndex.second).getOccupied() &&
			grid->at(squareIndex.first + iRow).at(squareIndex.second).getOccupant()->getPieceColor() == _gm->_currentTurn)
		{
			break;
		}
		if (grid->at(squareIndex.first + iRow).at(squareIndex.second).getOccupied() &&
			grid->at(squareIndex.first + iRow).at(squareIndex.second).getOccupant()->getPieceColor() != _gm->_currentTurn)
		{
			grid->at(squareIndex.first + iRow).at(squareIndex.second).setOverlayType(Square::TAKE);
			break;
		}
	}
}

void HighlightManager::orthoCaptureNegRowOptions(Square* square, Rules::RulePackage rules, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
{
	// Evaluate downward
	for (int iRow = -1; iRow >= rules.captureRules.row * -1; --iRow)
	{
		// Break if the row to evaluate goes above the size of the board
		if (squareIndex.first + iRow < 0)
		{
			break;
		}
		// Evaluate downward captures
		if (grid->at(squareIndex.first + iRow).at(squareIndex.second).getOccupied() &&
			grid->at(squareIndex.first + iRow).at(squareIndex.second).getOccupant()->getPieceColor() == _gm->_currentTurn)
		{
			break;
		}
		if (grid->at(squareIndex.first + iRow).at(squareIndex.second).getOccupied() &&
			grid->at(squareIndex.first + iRow).at(squareIndex.second).getOccupant()->getPieceColor() != _gm->_currentTurn)
		{
			grid->at(squareIndex.first + iRow).at(squareIndex.second).setOverlayType(Square::TAKE);
			break;
		}
	}
}

void HighlightManager::orthoCapturePosColOptions(Square* square, Rules::RulePackage rules, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
{
	// Evaluate right
	for (int iCol = 1; iCol <= rules.captureRules.column; ++iCol)
	{
		// Break if the column to evaluate goes above the size of the board
		if (squareIndex.second + iCol >= grid->size())
		{
			break;
		}
		// Evaluate right-side captures
		if (grid->at(squareIndex.first).at(squareIndex.second + iCol).getOccupied() &&
			grid->at(squareIndex.first).at(squareIndex.second + iCol).getOccupant()->getPieceColor() == _gm->_currentTurn)
		{
			break;
		}
		if (grid->at(squareIndex.first).at(squareIndex.second + iCol).getOccupied() &&
			grid->at(squareIndex.first).at(squareIndex.second + iCol).getOccupant()->getPieceColor() != _gm->_currentTurn)
		{
			grid->at(squareIndex.first).at(squareIndex.second + iCol).setOverlayType(Square::TAKE);
			break;
		}
	}
}

void HighlightManager::orthoCaptureNegColOptions(Square* square, Rules::RulePackage rules, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
{
	// Evaluate left
	for (int iCol = -1; iCol >= rules.captureRules.column * -1; --iCol)
	{
		// Break if the column to evaluate goes above the size of the board
		if (squareIndex.second + iCol < 0)
		{
			break;
		}
		// Evaluate upward captures
		if (grid->at(squareIndex.first).at(squareIndex.second + iCol).getOccupied() &&
			grid->at(squareIndex.first).at(squareIndex.second + iCol).getOccupant()->getPieceColor() == _gm->_currentTurn)
		{
			break;
		}
		if (grid->at(squareIndex.first).at(squareIndex.second + iCol).getOccupied() &&
			grid->at(squareIndex.first).at(squareIndex.second + iCol).getOccupant()->getPieceColor() != _gm->_currentTurn)
		{
			grid->at(squareIndex.first).at(squareIndex.second + iCol).setOverlayType(Square::TAKE);
			break;
		}
	}
}

void HighlightManager::highlightDiagCaptureOptions(Square* square, Rules::RulePackage rules)
{

	//captureOptionLoop(square, rules, [this](int iRow, int iCol, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
	//	{
	//		// If the square up one and right one from the selected square is occupied by an opponent's piece, put on the Take overlay.
	//		if (grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupied() &&
	//			grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupant()->getPieceColor() != _gm->_currentTurn)
	//		{
	//			grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).setOverlayType(Square::TAKE);
	//		}
	//	},
	//	[this](int iRow, int iCol, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
	//	{
	//		// Do the same thing, but to the left (negative on the board index)
	//		if (grid->at(squareIndex.first + iRow).at(squareIndex.second - iCol).getOccupied() &&
	//			grid->at(squareIndex.first + iRow).at(squareIndex.second - iCol).getOccupant()->getPieceColor() != _gm->_currentTurn)
	//		{
	//			grid->at(squareIndex.first + iRow).at(squareIndex.second - iCol).setOverlayType(Square::TAKE);
	//		}
	//	});

}