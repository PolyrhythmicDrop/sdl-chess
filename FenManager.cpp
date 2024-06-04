#include "FenManager.h"
#include "GameManager.h"
#include "easylogging++.h"

FenManager::FenManager(GameManager* gm) :
	_gm(gm),
	_history({}),
	_fenPosition("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"),
	_fenColor('w'),
	_fenCastle("KQkq"),
	_fenHalfMove('0'),
	_fenFullMove('0')
{};

std::string FenManager::createFenString()
{
	// Concatenate all the components of the FEN string
	std::string fen = _fenPosition + " " + _fenColor + " " + _fenCastle + " " + _fenPassant + " " + _fenHalfMove + " " + _fenFullMove;
	// Set the current FEN string
	_fenString = fen;
	// Add the string to the FEN history
	addToFenHistory(fen);
	// Return the string.
	return fen;
}

std::string FenManager::createFishFen()
{
	std::string fen = createFenString();

	std::string fishFen = "position fen " + fen + " moves " + _fenMove;

	return fishFen;
}

void FenManager::addToFenHistory(std::string move)
{
	_history.push_back(move);
}

std::vector<std::string>* FenManager::getFenHistory()
{
	return &_history;
}

void FenManager::clearFenHistory()
{
	_history.clear();
}

void FenManager::setFenMove(std::string move)
{
	_fenMove = move;
}

void FenManager::setFenPosition(std::string pos)
{
	_fenPosition = pos;
}

void FenManager::setFenColor(char color)
{
	_fenColor = color;
}

void FenManager::setCastleByColor(bool castle, int color, std::optional<bool> kingside, std::optional<bool> queenside)
{
	char king = '\0';
	char queen = '\0';

	if (castle)
	{
		switch (color)
		{
		case 0:
			if (kingside.has_value())
			{
				if (kingside == true)
				{
					king = 'k';
				}				
			}
			if (queenside.has_value())
			{
				if (queenside == true)
				{
					queen = 'q';
				}
			}
			_fenBlackCastle = king + queen;
			break;
		case 1:
			if (kingside.has_value())
			{
				if (kingside == true)
				{
					king = 'K';
				}
			}
			if (queenside.has_value())
			{
				if (queenside == true)
				{
					queen = 'Q';
				}
			}
			_fenWhiteCastle = king + queen;
			break;
		}
	}
	else
	{
		switch (color)
		{
		case 0:
			_fenBlackCastle = "";
			break;
		case 1:
			_fenWhiteCastle = "";
		}
	}
}

void FenManager::setFenCastle()
{
	_fenCastle = _fenWhiteCastle + _fenBlackCastle;
	if (_fenCastle == "")
	{
		_fenCastle = "-";
	}
}

void FenManager::setFenPassant(std::optional<std::string> squareName)
{
	if (squareName.has_value())
	{
		if (_fenPassant != "-")
		{
			_fenPassant = _fenPassant + squareName.value();
		}
		else
		{
			_fenPassant = squareName.value();
		}
	}
	else
	{
		_fenPassant = "-";
	}
}

void FenManager::removeFenPassantSquare(std::string squareName)
{
	auto sqIndex = _fenPassant.find(squareName);
	if (sqIndex != std::string::npos)
	{
		// Remove the square if found
		_fenPassant.erase(sqIndex, squareName.length());
		// If there are no other squares to en passant (jeez), set _fenPassant to "-"
		if (_fenPassant.size() == 0)
		{
			setFenPassant(std::nullopt);
		}
		else
		{
			return;
		}
	}
	else
	{
		LOG(DEBUG) << "Passant modifier square not found! Check your modifier.";
		return;
	}
}

void FenManager::plusFenHalfMove()
{
	++_fenHalfMove;
}

void FenManager::resetFenHalfMove()
{
	_fenHalfMove = 0;
}

void FenManager::plusFenFullMove()
{
	++_fenFullMove;
}