#pragma once
#include "GameObject.h"
#include "InputComponent.h"
#include "GraphicsComponent.h"

class Square;

class Piece : public GameObject
{
private:

	enum PieceColor {
		BLACK,
		WHITE
	};

	enum Figure {
		PAWN,
		BISHOP,
		KNIGHT,
		ROOK,
		QUEEN,
		KING
	};
	
	Square* _position;
	PieceColor _pieceColor;
	Figure _type;
	bool _selected;
	bool _alive;

	InputComponent* _input;
	GraphicsComponent* _graphics;

public:

	Piece(Figure type, PieceColor color);
	~Piece();

	inline void setPosition(Square* square) { _position = square; };
	inline Square* getPosition() { return _position; };

	inline const PieceColor getPieceColor() { return _pieceColor; };

	void changeType(Figure type);

	inline void setSelected(bool selected) { _selected = selected; };
	inline bool getSelected() { return _selected; };

	inline void setAlive(bool alive) { _alive = alive; };
	inline bool isAlive() { return _alive; };



};

