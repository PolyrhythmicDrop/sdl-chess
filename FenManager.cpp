#include "FenManager.h"
#include "GameManager.h"

FenManager::FenManager(GameManager* gm) :
	_gm(gm),
	_history({}),
	_fenPosition("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"),
	_fenColor('w'),
	_fenHalfMove('0'),
	_fenFullMove('0')
{};

std::string FenManager::createFenString()
{
	std::string fen = _fenPosition + _fenColor + _fenCastle + _fenPassant + _fenHalfMove + _fenFullMove;
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

std::string FenManager::setCastleByColor(bool castle, int color, bool kingside, bool queenside)
{
	char king, queen;
	std::string castleString = "";

	if (castle)
	{
		switch (color)
		{
		case 0:
			if (kingside)
			{
				king = 'k';
			}
			if (queenside)
			{
				queen = 'q';
			}
			break;
		case 1:
			if (kingside)
			{
				king = 'K';
			}
			if (queenside)
			{
				queen = 'Q';
			}
			break;
		}
	}
	else
	{
		return castleString;
	}
	
	castleString = king + queen;
	return castleString;

}

void FenManager::setFenCastle(std::string white, std::string black)
{
	std::string fenCastle = white + black;
	if (fenCastle == "")
	{
		_fenCastle = "-";
	}
	else
	{
		_fenCastle = fenCastle;
	}

}

void FenManager::setFenPassant(std::string squareName)
{
	_fenPassant = squareName;
}

void FenManager::plusFenHalfMove()
{
	++_fenHalfMove;
}

void FenManager::plusFenFullMove()
{
	++_fenFullMove;
}