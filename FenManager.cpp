#include "FenManager.h"
#include "GameManager.h"
#include "easylogging++.h"
#include <sstream>

FenManager::FenManager(GameManager* gm) :
	_gm(gm),
	_history({}),
	_fenPosition({}),
	_fenColor('w'),
	_fenHalfMove(0),
	_fenFullMove(0)
{};

std::string FenManager::createFenString()
{
	std::stringstream moveCounter{};
	moveCounter << _fenHalfMove << ' ' << _fenFullMove;
	
	// Concatenate all the components of the FEN string
	std::string fen = _fenPosition + " " + _fenColor + " " + _fenCastle + " " + _fenPassant + " " + moveCounter.str();
	// Set the current FEN string
	_fenString = fen;
	// Return the string.
	return fen;
}

void FenManager::parseFenString(std::string fen)
{
	std::string position{};
	char color{};
	std::string castle{};
	std::string passant{};
	int halfMove{};
	int fullMove{};

	int posSize{};
	int colorIndex{};
	int castleSize{};
	int passantSize{};
	int halfSize{};
	int fullSize{};

	std::string::iterator fenItr{ fen.begin() };
	std::string::iterator fenPrevItr{};

	// Get position substring
	fenItr = std::find(fen.begin(), fen.end(), ' ');
	if (fenItr != fen.end())
	{
		posSize = std::distance(fen.begin(), fenItr);
		position = fen.substr(0, posSize);
		_fenPosition = position;
		fenPrevItr = fenItr;
		++fenItr;
	}

	if (fenItr != fen.end())
	{
		colorIndex = std::distance(fen.begin(), fenItr);
		color = fen.at(colorIndex);
		_fenColor = color;
		fenItr = fenItr + 2;
		fenPrevItr = fenItr;
	}

	// Get castle string
	fenItr = std::find(fenItr, fen.end(), ' ');
	if (fenItr != fen.end())
	{
		castleSize = std::distance(fenPrevItr, fenItr);
		castle = fen.substr(std::distance(fen.begin(), fenPrevItr), castleSize);
		_fenCastle = castle;

		// Get the individual components of the castle string
		for (char c : castle)
		{
			switch (c)
			{
			case 'k':
				_blackKingside.push_back(c);
				break;
			case 'K':
				_whiteKingside.push_back(c);
				break;
			case 'q':
				_blackQueenside.push_back(c);
				break;
			case 'Q':
				_whiteQueenside.push_back(c);
			}
		}
		_fenWhiteCastle = _whiteKingside + _whiteQueenside;
		_fenBlackCastle = _blackKingside + _blackQueenside;
		updateFenCastle();

		++fenItr;
		fenPrevItr = fenItr;
	}

	// Get passant string
	fenItr = std::find(fenItr, fen.end(), ' ');
	if (fenItr != fen.end())
	{
		passantSize = std::distance(fenPrevItr, fenItr);
		passant = fen.substr(std::distance(fen.begin(), fenPrevItr), passantSize);
		_fenPassant = passant;
		++fenItr;
		fenPrevItr = fenItr;
	}

	// Get the half-move count
	fenItr = std::find(fenItr, fen.end(), ' ');
	if (fenItr != fen.end())
	{ 
		halfSize = std::distance(fenPrevItr, fenItr);
		halfMove = std::stoi(fen.substr(std::distance(fen.begin(), fenPrevItr), halfSize));
		_fenHalfMove = halfMove;
		++fenItr;
		fenPrevItr = fenItr;
	}

	// Get the full-move count
	fenItr = std::find(fenItr, fen.end(), ' ');

	fullSize = std::distance(fenPrevItr, fenItr);
	fullMove = std::stoi(fen.substr(std::distance(fen.begin(), fenPrevItr), fullSize));
	_fenFullMove = fullMove;
	fenPrevItr = fenItr;

	createFenString();
	
}

std::string FenManager::createFishFen(std::string fen, bool move)
{
	std::string fishFen = "";

	if (!move)
	{
		fishFen = "position fen " + fen;
	}
	else
	{
		fishFen = "position fen " + fen + " moves " + _fenMove;
	}

	return fishFen;
}

void FenManager::addToFenHistory(std::string move)
{
	_history.push_back(move);
	// Debug checking
	LOG(TRACE) << move;
}

std::vector<std::string>* FenManager::getFenHistory()
{
	return &_history;
}

void FenManager::clearFenHistory()
{
	_history.clear();
}

void FenManager::addPromoteToFenMove(char piece)
{
	_fenMove.push_back(piece);
}

void FenManager::setFenMove(std::string startSq, std::string targetSq)
{
	_fenMove = startSq + targetSq;
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
	if (castle)
	{
		switch (color)
		{
		case 0:
			if (kingside.has_value())
			{
				if (kingside.value() == true)
				{
					_blackKingside = 'k';
				}
				else if (kingside.value() == false)
				{
					_blackKingside = "";
				}
			}
			else
			{
				_blackKingside = _blackKingside;
			}
			if (queenside.has_value())
			{
				if (queenside.value() == true)
				{
					_blackQueenside = 'q';
				}
				else if (queenside.value() == false)
				{
					_blackQueenside = "";
				}
			}
			else
			{
				_blackQueenside = _blackQueenside;
			}
			_fenBlackCastle = _blackKingside + _blackQueenside;
			break;
		case 1:
			if (kingside.has_value())
			{
				if (kingside.value() == true)
				{
					_whiteKingside = 'K';
				}
				else if (kingside.value() == false)
				{
					_whiteKingside = "";
				}
			}
			else
			{
				_whiteKingside = _whiteKingside;
			}
			if (queenside.has_value())
			{
				if (queenside == true)
				{
					_whiteQueenside = 'Q';
				}
				else if (queenside.value() == false)
				{
					_whiteQueenside = "";
				}
			}
			else
			{
				_whiteQueenside = _whiteQueenside;
			}
			_fenWhiteCastle = _whiteKingside + _whiteQueenside;
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
			break;
		}
	}
}

void FenManager::updateFenCastle()
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
		_fenPassant = squareName.value();
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
	// Set to -1, since the reset occurs right after a pawn is moved or a piece captured, but technically before the end of the turn.
	// Since the half move counter increments at the end of a player's turn, it will be 0 at the start of the next player's turn if it was reset during the previous turn.
	_fenHalfMove = -1;
}

void FenManager::plusFenFullMove()
{
	++_fenFullMove;
}