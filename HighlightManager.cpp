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
		// Evaluate leftward movement
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
	Rules::RulePackage rules = _gm->getRules()->getRulesPackage(piece->getFenName(), piece->getFirstMove());

	return rules;

}

Rules::RulePackage HighlightManager::getPieceRules(char fen, bool firstMove)
{
	Rules::RulePackage rules = _gm->getRules()->getRulesPackage(fen, firstMove);
	return rules;

}

void HighlightManager::highlightActionOptions(Square* square)
{

	// Check for castle
	if (square->getOccupant()->getPieceType() == Piece::KING)
	{
		_gm->checkForCastle(square->getOccupant());
	}

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

bool HighlightManager::highlightCheck(Square* square)
{

	Piece::PieceColor turnColor;
	// Set the color to measure pawn rules against. Should be the opposite color of the turn.
	char pawn;
	switch (_gm->getTurn())
	{
	case 0:
		turnColor = Piece::BLACK;
		pawn = 'P';
		break;
	case 1:
		turnColor = Piece::WHITE;
		pawn = 'p';
		break;
	default:
		turnColor = Piece::BLACK;
		pawn = 'P';
		break;
	}

	bool check = false;
	
	for (int i = 0; i < 1 && !check; ++i)
	{
		// Check the orthogonal and diagonal moves by getting the queen ruleset. Put a check overlay on any opposing pieces you encounter.
		orthoHighlightOptions(square, getPieceRules('Q'), [this](int iRow, int iCol, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
			{
				grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).setOverlayType(Square::NONE);
			},
			[this, &check](int iRow, int iCol, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
			{
				// if the piece encountered is not an enemy pawn or knight, set check. (different rule set to check for pawns and knights)
				if (grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupant()->getPieceType() == Piece::ROOK ||
					grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupant()->getPieceType() == Piece::QUEEN)
				{
					grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).setOverlayType(Square::CHECK);
					check = true;
				}
			});
		diagHighlightOptions(square, getPieceRules('Q'), [this](int iRow, int iCol, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
			{
				grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).setOverlayType(Square::NONE);
			},
			[this, &check](int iRow, int iCol, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
			{
				// if the piece encountered is not an enemy pawn or knight, set check. (different rule set to check for pawns and knights)
				if (grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupant()->getPieceType() == Piece::BISHOP ||
					grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupant()->getPieceType() == Piece::QUEEN)
				{
					grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).setOverlayType(Square::CHECK);
					check = true;
				}
			});
		// Check the orthogonal and diagonal moves for opposing kings by getting the king ruleset. Put a check overlay on any opposing pieces you encounter.
		orthoHighlightOptions(square, getPieceRules('K'), [this](int iRow, int iCol, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
			{
				grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).setOverlayType(Square::NONE);
			},
			[this, &check](int iRow, int iCol, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
			{
				// if the piece encountered is not an enemy pawn or knight, set check. (different rule set to check for pawns and knights)
				if (grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupant()->getPieceType() == Piece::KING)
				{
					grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).setOverlayType(Square::CHECK);
					check = true;
				}
			});
		diagHighlightOptions(square, getPieceRules('K'), [this](int iRow, int iCol, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
			{
				grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).setOverlayType(Square::NONE);
			},
			[this, &check](int iRow, int iCol, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
			{
				// if the piece encountered is not an enemy pawn or knight, set check. (different rule set to check for pawns and knights)
				if (grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupant()->getPieceType() == Piece::KING)
				{
					grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).setOverlayType(Square::CHECK);
					check = true;
				}
			});
		// Capture highlighting for pawns. Don't need to check orthogonal movement because pawns can't capture orthogonally.
		diagHighlightOptions(square, getPieceRules(pawn), [this](int iRow, int iCol, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
			{
				grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).setOverlayType(Square::NONE);
			},
			[this, square, &check](int iRow, int iCol, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
			{
				// If the piece encountered is a black pawn and the checked square is one row below the pawn, set check.
				// This function already checks to see whether the piece encountered is an enemy piece to get to this point, so if it is black's turn, this will not run.
				if (grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupant()->getFenName() == 'p' &&
					square->getBoardIndex().first == grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getBoardIndex().first - 1)
				{
					grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).setOverlayType(Square::CHECK);
					check = true;
				}
				// Else if the piece encountered is a white pawn and the checked square is one row above the pawn, set check.
				// This function already checks to see whether the piece encountered is an enemy piece to get to this point, so if it is white's turn, this will not run.
				else if (grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupant()->getFenName() == 'P' &&
					square->getBoardIndex().first == grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getBoardIndex().first + 1)
				{
					grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).setOverlayType(Square::CHECK);
					check = true;
				}
			});
		// Check for knight check using the fake knight
		jumpHighlightOptions(square, getPieceRules('N'), [this](int iRow, int iCol, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
			{
				grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).setOverlayType(Square::NONE);
			},
			[this, &check](int iRow, int iCol, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex)
			{
				// if the piece encountered is an enemy knight, set check.
				if (grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).getOccupant()->getPieceType() == Piece::KNIGHT)
				{
					grid->at(squareIndex.first + iRow).at(squareIndex.second + iCol).setOverlayType(Square::CHECK);
					check = true;
				}
			});
	}
		
	_gm->getCurrentPlayer()->setCheck(check);

	return check;
}

void HighlightManager::highlightCastle(Piece* king, Square* rookLSq, Square* rookRSq)
{
	std::vector<std::vector<Square>>* grid = _gm->_gameScene->getBoard()->getBoardGrid();
	std::pair<int, int> kingIndex = king->getSquare()->getBoardIndex();

	bool castle = true;

	// Highlight castling toward the left rook first.
	if (rookLSq != nullptr)
	{
		while (castle)
		{
			// Black castle checking on the left.
			if (_gm->_currentTurn == 0)
			{
				// Gap is the rook column - the king column. Since we're checking left, the gap will be negative until it iterates up to 0.
				for (int gap = rookLSq->getBoardIndex().second - kingIndex.second + 1; gap < 0; ++gap)
				{
					// If any square between the rook and the king is occupied, break and stop checking for castle.
					if (grid->at(7).at(kingIndex.second + gap).getOccupied() == true)
					{
						castle = false;
						break;
					}
				}
				if (!castle)
				{
					break;
				}
				for (int kingMove = 1; kingMove <= 2; ++kingMove)
				{
					king->getSquare()->setOccupied(false);
					// Temporarily set the king's position so we can check it for check.
					king->setSquare(&grid->at(7).at(kingIndex.second - kingMove));
					// Check if any square that the king will pass through would result in a check.
					if (highlightCheck(&grid->at(7).at(kingIndex.second - kingMove)))
					{
						// Reset the king's position to its initial position.
						king->getSquare()->setOccupied(false);
						king->setSquare(&grid->at(kingIndex.first).at(kingIndex.second));
						// Set castle to false and break out of the loop.
						castle = false;
						break;
					}
				}
				if (!castle)
				{
					break;
				}
				// Reset the king's position to its initial position.
				king->getSquare()->setOccupied(false);
				king->setSquare(&grid->at(kingIndex.first).at(kingIndex.second));
				king->getSquare()->setOccupied(true, king);
				// Set the overlay to CASTLE for the square the king will move to, two spaces to the king's left.
				grid->at(7).at(kingIndex.second - 2).setOverlayType(Square::CASTLE);
				castle = false;
				break;
			}

			castle = false;
		}
	}
}


