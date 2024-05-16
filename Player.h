#pragma once
#include "Piece.h"

class Player
{
public:

	Player(Piece::PieceColor color);
	~Player() {};

	Piece::PieceColor const _playerColor;

};

