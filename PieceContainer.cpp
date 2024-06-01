#include "PieceContainer.h"
#include "PieceIterator.h"
#include "easylogging++.h"

PieceContainer::PieceContainer() :
	_pieces(),
	_capturedPieces({})
{
	_pieces.reserve(32);
	initializePieces();
	_capturedPieces.clear();
}

PieceIterator PieceContainer::createIterator()
{
	PieceIterator pieceItr(this);
	return pieceItr;
}

void PieceContainer::initializePieces()
{
	// Instantiate the white pieces and add them to the _pieces vector
	Piece whtPawn(Piece::PAWN, Piece::WHITE);
	Piece whtPawn1(Piece::PAWN, Piece::WHITE);
	Piece whtPawn2(Piece::PAWN, Piece::WHITE);
	Piece whtPawn3(Piece::PAWN, Piece::WHITE);
	Piece whtPawn4(Piece::PAWN, Piece::WHITE);
	Piece whtPawn5(Piece::PAWN, Piece::WHITE);
	Piece whtPawn6(Piece::PAWN, Piece::WHITE);
	Piece whtPawn7(Piece::PAWN, Piece::WHITE);


	_pieces.push_back(whtPawn);
	_pieces.push_back(whtPawn1);
	_pieces.push_back(whtPawn2);
	_pieces.push_back(whtPawn3);
	_pieces.push_back(whtPawn4);
	_pieces.push_back(whtPawn5);
	_pieces.push_back(whtPawn6);
	_pieces.push_back(whtPawn7);

	Piece whtRook(Piece::ROOK, Piece::WHITE);
	Piece whtRook1(Piece::ROOK, Piece::WHITE);

	_pieces.push_back(whtRook);
	_pieces.push_back(whtRook1);

	Piece whtKnight(Piece::KNIGHT, Piece::WHITE);
	Piece whtKnight1(Piece::KNIGHT, Piece::WHITE);

	_pieces.push_back(whtKnight);
	_pieces.push_back(whtKnight1);

	Piece whtBishop(Piece::BISHOP, Piece::WHITE);
	Piece whtBishop1(Piece::BISHOP, Piece::WHITE);

	_pieces.push_back(whtBishop);
	_pieces.push_back(whtBishop1);

	Piece whtQueen(Piece::QUEEN, Piece::WHITE);

	_pieces.push_back(whtQueen);

	Piece whtKing(Piece::KING, Piece::WHITE);

	_pieces.push_back(whtKing);

	// Instantiate the black pieces and add them to the _pieces vector
	Piece blkPawn(Piece::PAWN, Piece::BLACK);
	Piece blkPawn1(Piece::PAWN, Piece::BLACK);
	Piece blkPawn2(Piece::PAWN, Piece::BLACK);
	Piece blkPawn3(Piece::PAWN, Piece::BLACK);
	Piece blkPawn4(Piece::PAWN, Piece::BLACK);
	Piece blkPawn5(Piece::PAWN, Piece::BLACK);
	Piece blkPawn6(Piece::PAWN, Piece::BLACK);
	Piece blkPawn7(Piece::PAWN, Piece::BLACK);

	_pieces.push_back(blkPawn);
	_pieces.push_back(blkPawn1);
	_pieces.push_back(blkPawn2);
	_pieces.push_back(blkPawn3);
	_pieces.push_back(blkPawn4);
	_pieces.push_back(blkPawn5);
	_pieces.push_back(blkPawn6);
	_pieces.push_back(blkPawn7);

	Piece blkRook(Piece::ROOK, Piece::BLACK);
	Piece blkRook1(Piece::ROOK, Piece::BLACK);

	_pieces.push_back(blkRook);
	_pieces.push_back(blkRook1);

	Piece blkKnight(Piece::KNIGHT, Piece::BLACK);
	Piece blkKnight1(Piece::KNIGHT, Piece::BLACK);

	_pieces.push_back(blkKnight);
	_pieces.push_back(blkKnight1);

	Piece blkBishop(Piece::BISHOP, Piece::BLACK);
	Piece blkBishop1(Piece::BISHOP, Piece::BLACK);

	_pieces.push_back(blkBishop);
	_pieces.push_back(blkBishop1);

	Piece blkQueen(Piece::QUEEN, Piece::BLACK);

	_pieces.push_back(blkQueen);

	Piece blkKing(Piece::KING, Piece::BLACK);

	_pieces.push_back(blkKing);

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