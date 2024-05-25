#include "GameScene.h"
#include "HighlightManager.h"
#include "easylogging++.h"
#include "GameManager.h"

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
void HighlightManager::orthoHighlightOptions(Square* square, Rules::RulePackage rules, M m, T t)
{
	std::vector<std::vector<Square>>* grid = _gm->_gameScene->getBoard()->getBoardGrid();
	std::pair<int, int> squareIndex = square->getBoardIndex();

	bool finished = false;
	int iCol = 0;
	int iRow = 0;

	// Up
	for (int iRow = 1; iRow <= rules.moveRules.row && !finished; ++iRow)
	{
		// Break if the row to evaluate goes above the size of the board
		if (squareIndex.first + iRow >= grid->size())
		{
			finished = true;
			break;
		}
		// Evaluate upward movement
		if (!grid->at(squareIndex.first + iRow).at(squareIndex.second).getOccupied())
		{
			// If the piece can move orthogonally and is not a black pawn (which can only move down).
			if (rules.moveRules.orthoMove == true && square->getOccupant()->getFenName() != 'p')
			{
				m(iRow, iCol, grid, squareIndex);
			}
		}
		// Stop adding movement overlays once you encounter another piece
		else if (grid->at(squareIndex.first + iRow).at(squareIndex.second).getOccupied() && grid->at(squareIndex.first + iRow).at(squareIndex.second).getOccupant()->getPieceColor() != _gm->_currentTurn)
		{
			if (rules.captureRules.orthoCapture == true)
			{
				t(iRow, iCol, grid, squareIndex);
			}
			finished = true;
			break;
		}
		else
		{
			finished = true;
			break;
		}
	}

	finished = false;

	// Down
	for (int iRow = -1; iRow >= rules.moveRules.row * -1 && !finished; --iRow)
	{
		// Break if the row to evaluate goes above the size of the board
		if (squareIndex.first + iRow >= grid->size())
		{
			finished = true;
			break;
		}
		// Evaluate upward movement
		if (!grid->at(squareIndex.first + iRow).at(squareIndex.second).getOccupied())
		{
			// If the piece can move orthogonally and is not a white pawn (which can only move up).
			if (rules.moveRules.orthoMove == true && square->getOccupant()->getFenName() != 'P')
			{
				m(iRow, iCol, grid, squareIndex);
			}
		}
		// Stop adding movement overlays once you encounter another piece
		else if (grid->at(squareIndex.first + iRow).at(squareIndex.second).getOccupied() && grid->at(squareIndex.first + iRow).at(squareIndex.second).getOccupant()->getPieceColor() != _gm->_currentTurn)
		{
			if (rules.captureRules.orthoCapture == true)
			{
				t(iRow, iCol, grid, squareIndex);
			}
			finished = true;
			break;
		}
		else
		{
			finished = true;
			break;
		}
	}

	finished = false;

	iRow = 0;

	// Left
	for (int iCol = -1; iCol >= rules.moveRules.column * -1 && !finished; --iCol)
	{
		// Break if the row to evaluate goes above the size of the board
		if (squareIndex.second + iCol >= grid->size())
		{
			finished = true;
			break;
		}
		// Evaluate upward movement
		if (!grid->at(squareIndex.first).at(squareIndex.second + iCol).getOccupied())
		{
			// If the piece can move orthogonally and is not a pawn (which can't move left or right).
			if (rules.moveRules.orthoMove == true && square->getOccupant()->getPieceType() != 0)
			{
				m(iRow, iCol, grid, squareIndex);
			}
		}
		// Stop adding movement overlays once you encounter another piece
		else if (grid->at(squareIndex.first).at(squareIndex.second + iCol).getOccupied() && grid->at(squareIndex.first).at(squareIndex.second + iCol).getOccupant()->getPieceColor() != _gm->_currentTurn)
		{
			if (rules.captureRules.orthoCapture == true)
			{
				t(iRow, iCol, grid, squareIndex);
			}
			finished = true;
			break;
		}
		else
		{
			finished = true;
			break;
		}
	}

	finished = false;

	// Right
	for (int iCol = 1; iCol <= rules.moveRules.column && !finished; ++iCol)
	{
		// Break if the row to evaluate goes above the size of the board
		if (squareIndex.second + iCol >= grid->size())
		{
			finished = true;
			break;
		}
		// Evaluate upward movement
		if (!grid->at(squareIndex.first).at(squareIndex.second + iCol).getOccupied())
		{
			// If the piece can move orthogonally and is not a pawn (which can't move left or right).
			if (rules.moveRules.orthoMove == true && square->getOccupant()->getPieceType() != 0)
			{
				m(iRow, iCol, grid, squareIndex);
			}
		}
		// Stop adding movement overlays once you encounter another piece
		else if (grid->at(squareIndex.first).at(squareIndex.second + iCol).getOccupied() && grid->at(squareIndex.first).at(squareIndex.second + iCol).getOccupant()->getPieceColor() != _gm->_currentTurn)
		{
			if (rules.captureRules.orthoCapture == true)
			{
				t(iRow, iCol, grid, squareIndex);
			}
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


template<typename M, typename T>
void HighlightManager::diagHighlightOptions(Square* square, Rules::RulePackage rules, M m, T t)
{
	std::vector<std::vector<Square>>* grid = _gm->_gameScene->getBoard()->getBoardGrid();
	std::pair<int, int> squareIndex = square->getBoardIndex();

	bool finished = false;

	// Up-right
	for (int iRow = 1; iRow <= rules.moveRules.row && !finished; ++iRow)
	{
		for (int iCol = 1; (iCol <= rules.moveRules.column || iCol <= rules.captureRules.column) && !finished; ++iCol)
		{
			// Break if we exceed the size of the board
			if (squareIndex.first + iRow >= grid->size() || squareIndex.second + iCol >= grid->size())
			{
				finished = true;
				break;
			}
			if (!grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupied())
			{
				if (rules.moveRules.diagMove)
				{
					m(iRow, iCol, grid, squareIndex);
				}
				++iRow;
			}
			else if (grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupied() &&
				grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupant()->getPieceColor() != _gm->_currentTurn)
			{
				// If the piece can capture diagonally and it is not a black pawn (which can't move/capture up)
				if (rules.captureRules.diagCapture && square->getOccupant()->getFenName() != 'p' && iCol <= rules.captureRules.column)
				{
					t(iRow, iCol, grid, squareIndex);
				}
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
		for (int iCol = 1; iCol <= rules.moveRules.column || iCol <= rules.captureRules.column && !finished; ++iCol)
		{
			// Break if we exceed the size of the board
			if (squareIndex.first + iRow >= grid->size() || squareIndex.second + iCol >= grid->size())
			{
				finished = true;
				break;
			}
			if (!grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupied())
			{
				if (rules.moveRules.diagMove)
				{
					m(iRow, iCol, grid, squareIndex);
				}
				--iRow;
			}
			else if (grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupied() &&
				grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupant()->getPieceColor() != _gm->_currentTurn)
			{
				// If the piece can capture diagonally and it is not a white pawn (which can't move/capture down)
				if (rules.captureRules.diagCapture && square->getOccupant()->getFenName() != 'P' && iCol <= rules.captureRules.column)
				{
					t(iRow, iCol, grid, squareIndex);
				}
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
		for (int iCol = -1; iCol >= rules.moveRules.column * -1 || iCol >= rules.captureRules.column * -1 && !finished; --iCol)
		{
			// Break if we exceed the size of the board
			if (squareIndex.first + iRow >= grid->size() || squareIndex.second + iCol >= grid->size())
			{
				finished = true;
				break;
			}
			if (!grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupied())
			{
				if (rules.moveRules.diagMove)
				{
					m(iRow, iCol, grid, squareIndex);
				}
				++iRow;
			}
			else if (grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupied() &&
				grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupant()->getPieceColor() != _gm->_currentTurn)
			{
				if (rules.captureRules.diagCapture && square->getOccupant()->getFenName() != 'p' && iCol >= rules.captureRules.column * -1)
				{
					t(iRow, iCol, grid, squareIndex);
				}
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
		for (int iCol = -1; iCol >= rules.moveRules.column * -1 || iCol >= rules.captureRules.column * -1 && !finished; --iCol)
		{
			// Break if we exceed the size of the board
			if (squareIndex.first + iRow >= grid->size() || squareIndex.second + iCol >= grid->size())
			{
				finished = true;
				break;
			}
			if (!grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupied())
			{
				if (rules.moveRules.diagMove)
				{
					m(iRow, iCol, grid, squareIndex);
				}
				--iRow;
			}
			else if (grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupied() &&
				grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupant()->getPieceColor() != _gm->_currentTurn)
			{
				if (rules.captureRules.diagCapture && square->getOccupant()->getFenName() != 'P' && iCol >= rules.captureRules.column * -1)
				{
					t(iRow, iCol, grid, squareIndex);
				}
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

	// Functionality to account for en passant
	// If the rules allow for en passant (i.e. if the piece on the square is a pawn) 
	// and a square either to the right or left of it contains a passantable pawn,
	// highlight the square behind the passantable pawn with the capture overlay.
	if (rules.captureRules.enPassant == true)
	{
			// Check if the square to the left contains a passantable pawn, if it is within the board
			if (squareIndex.second - 1 < grid->size() &&
				grid->at(squareIndex.first).at(squareIndex.second - 1).getOccupied() &&
				grid->at(squareIndex.first).at(squareIndex.second - 1).getOccupant()->getPassantable())
			{
				switch (square->getOccupant()->getFenName())
				{
				case 'P':
					t(1, -1, grid, squareIndex);
					break;
				case 'p':
					t(-1, -1, grid, squareIndex);
				}
			}
			// Check if the square to the right contains a passantable pawn, if it is within the board
			if (squareIndex.second + 1 < grid->size() &&
				grid->at(squareIndex.first).at(squareIndex.second + 1).getOccupied() &&
				grid->at(squareIndex.first).at(squareIndex.second + 1).getOccupant()->getPassantable())
			{
				switch (square->getOccupant()->getFenName())
				{
				case 'P':
					t(1, 1, grid, squareIndex);
					break;
				case 'p':
					t(-1, 1, grid, squareIndex);
				}
			}
	}

}

template<typename M, typename T>
void HighlightManager::jumpHighlightOptions(Square* square, Rules::RulePackage rules, M m, T t)
{
	std::vector<std::vector<Square>>* grid = _gm->_gameScene->getBoard()->getBoardGrid();
	std::pair<int, int> squareIndex = square->getBoardIndex();

	int iRow = 0;
	int iCol = 0;

	for (int i = 0; i < 8; ++i)
	{
		switch (i)
		{
		case 0:
			iRow = 2;
			iCol = 1;
			break;
		case 1:
			iRow = 2;
			iCol = -1;
			break;
		case 2:
			iRow = 1;
			iCol = 2;
			break;
		case 3:
			iRow = 1;
			iCol = -2;
			break;
		case 4:
			iRow = -1;
			iCol = 2;
			break;
		case 5:
			iRow = -1;
			iCol = -2;
			break;
		case 6:
			iRow = -2;
			iCol = 1;
			break;
		case 7:
			iRow = -2;
			iCol = -1;
			break;
		default:
			LOG(ERROR) << "Jump switch statement is busted!";
			break;
		}
		if (squareIndex.first + iRow < grid->size() && squareIndex.second + iCol < grid->size())
		{
			if (!grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupied())
			{
				m(iRow, iCol, grid, squareIndex);
			}
			else if (grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupant()->getPieceColor() != _gm->_currentTurn)
			{
				t(iRow, iCol, grid, squareIndex);
			}
		}
		else
		{
			continue;
		}
	}
}


// *********************** //

Rules::RulePackage HighlightManager::getPieceRules(Piece* piece)
{
	Rules::RulePackage rules = _gm->getRules()->getRulesPackage(piece);

	return rules;
}

void HighlightManager::highlightActionOptions(Square* square)
{

	Rules::RulePackage rules = getPieceRules(square->getOccupant());

	// Compute orthogonal moves
	if (rules.moveRules.orthoMove || rules.captureRules.orthoCapture)
	{
		highlightOrthoMoveOptions(square, rules);
	}

	// Compute diagonal moves
	if (rules.moveRules.diagMove || rules.captureRules.diagCapture )
	{
		highlightDiagMoveOptions(square, rules);
	}

	// Compute jump moves
	if (rules.moveRules.jumpMove || rules.captureRules.jumpCapture)
	{
		highlightJumpMoveOptions(square, rules);
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

	orthoHighlightOptions(square, rules, [this](int iRow, int iCol, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
		{
			grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).setOverlayType(Square::MOVE);
		},
		[this](int iRow, int iCol, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
		{
			grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).setOverlayType(Square::TAKE);
		});

}


void HighlightManager::highlightDiagMoveOptions(Square* square, Rules::RulePackage rules)
{
	
	diagHighlightOptions(square, rules, [this](int iRow, int iCol, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
		{
			grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).setOverlayType(Square::MOVE);
		},
		[this](int iRow, int iCol, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex) 
		{
			grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).setOverlayType(Square::TAKE);
		});


}

void HighlightManager::highlightJumpMoveOptions(Square* square, Rules::RulePackage rules)
{
	jumpHighlightOptions(square, rules, [this](int iRow, int iCol, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
		{
			grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).setOverlayType(Square::MOVE);
		},
		[this](int iRow, int iCol, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
		{
			grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).setOverlayType(Square::TAKE);
		});
}


