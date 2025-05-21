#include "PieceContainer.h"
#include "PieceIterator.h"
#include "easylogging++.h"

PieceContainer::PieceContainer() :
	_pieces(),
	_capturedPieces({})
{
	_pieces.reserve(32);
	_capturedPieces.clear();
}

PieceIterator PieceContainer::createIterator()
{
	PieceIterator pieceItr(this);
	return pieceItr;
}

void PieceContainer::initializePieces(std::string fen)
{

	for (char p : fen)
	{
		switch (p)
		{
		case 'p':
			_pieces.push_back(Piece{ Piece::PAWN, Piece::BLACK });
			break;
		case 'P':
			_pieces.push_back(Piece{ Piece::PAWN, Piece::WHITE });
			break;
		case 'r':
			_pieces.push_back(Piece { Piece::ROOK, Piece::BLACK });
			break;
		case 'R':
			_pieces.push_back(Piece { Piece::ROOK, Piece::WHITE });
			break;
		case 'n':
			_pieces.push_back(Piece { Piece::KNIGHT, Piece::BLACK });
			break;
		case 'N':
			_pieces.push_back(Piece{ Piece::KNIGHT, Piece::WHITE });
			break;
		case 'b':
			_pieces.push_back(Piece{ Piece::BISHOP, Piece::BLACK});
			break;
		case 'B':
			_pieces.push_back(Piece{ Piece::BISHOP, Piece::WHITE});
			break;
		case 'q':
			_pieces.push_back(Piece{ Piece::QUEEN, Piece::BLACK});
			break;
		case 'Q':
			_pieces.push_back(Piece{ Piece::QUEEN, Piece::WHITE});
			break;
		case 'k':
			_pieces.push_back(Piece{ Piece::KING, Piece::BLACK});
			break;
		case 'K':
			_pieces.push_back(Piece{ Piece::KING, Piece::WHITE});
			break;
		default:
			break;
		}
	}

	LOG(TRACE) << _pieces.size() << " pieces added to Game Scene!";

}



std::vector<int> PieceContainer::getPieceIndexByFEN(char fen)
{

	std::vector<int> foundPieceIndexes;
	// Create an iterator for the Piece vector
	PieceIterator itr = createIterator();
	itr.goToStart();

	do
	{
		itr.updatePositions(std::find_if(itr.getCurrentPosition(), itr.getContainerEnd(), [&](Piece& piece) {
			return piece.getFenName() == fen;
			}));
		if (!itr.isDone())
		{
			int index = itr.getIndex();
			foundPieceIndexes.push_back(index);
			itr.goForward(1);
		}
		else
		{
			break;
		}
	} while (!itr.isDone());

	return foundPieceIndexes;

}

std::vector<Piece*> PieceContainer::getPiecesByFen(char fen)
{
	std::vector<Piece*> fenPieces;
	std::vector<int> indexVect = getPieceIndexByFEN(fen);

	for (int i = 0; i < indexVect.size(); ++i)
	{
		fenPieces.push_back(&_pieces.at(indexVect[i]));
	}

	return fenPieces;

}

void PieceContainer::addToCapturedPieces(Piece* piece)
{
	if (piece->isAlive() == false)
	{
		_capturedPieces.push_back(piece);
	}

}

std::vector<Piece*> PieceContainer::getCapturedPiecesByColor(int color)
{


	std::vector<Piece*> piecesBlk;
	std::vector<Piece*> piecesWht;

	for (int i = 0; i < _capturedPieces.size(); ++i)
	{
		if (_capturedPieces.at(i)->getPieceColor() == Piece::BLACK)
		{
			piecesBlk.push_back(_capturedPieces.at(i));
		}
		else if (_capturedPieces.at(i)->getPieceColor() == Piece::WHITE)
		{
			piecesWht.push_back(_capturedPieces.at(i));
		}
	}

	if (color == 0)
	{
		return piecesBlk;
	}
	else if (color == 1)
	{
		return piecesWht;
	}
	else
	{
		LOG(ERROR) << "Specify a piece color! Must be 0 or 1.";
		piecesBlk.clear();
		return piecesBlk;
	}
}

Piece* PieceContainer::getLastCapturedPiece()
{
	Piece* capturedPiece = nullptr;
	if (_capturedPieces.size() > 0)
	{
		capturedPiece = _capturedPieces.back();
	}
	return capturedPiece;
}

void PieceContainer::removePieceFromCapturedPieces(Piece* piece)
{
	std::vector<Piece*>::iterator itr = std::find(_capturedPieces.begin(), _capturedPieces.end(), piece);

	if (itr != _capturedPieces.end())
	{
		_capturedPieces.erase(itr);
	}

}