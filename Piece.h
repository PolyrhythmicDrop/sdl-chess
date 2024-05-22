#pragma once
#include "GameObject.h"
#include "PieceInputComponent.h"
#include "PieceGraphicsComponent.h"

class Square;

class Piece : public GameObject
{
public:

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

	Piece(Figure type, PieceColor color);
	Piece(const Piece& piece);
	Piece& operator=(const Piece& other);

	~Piece();

	inline char getFenName() const { if (_fenName != NULL) { return _fenName; } };

	void setPosition(Square* square);
	inline Square* getPosition() { return _position; };

	inline const PieceColor getPieceColor() const { return _pieceColor; };
	inline const Figure getPieceType() const { return _type; };

	void changeType(Figure type);

	void setSelected(bool selected);
	inline bool getSelected() const { return _selected; };

	inline void setAlive(bool alive) { _alive = alive; };
	inline bool isAlive() const { return _alive; };

	inline void setFirstMove(bool first) { _firstMove = first; };
	inline bool getFirstMove() const { return _firstMove; };

	inline PieceInputComponent* getInput() { return _input; };
	inline PieceGraphicsComponent* getGraphics() { return _graphics; };

private:

	void setFenName(char fen);
	
	Square* _position;
	PieceColor _pieceColor;
	Figure _type;
	char _fenName;
	bool _firstMove;
	bool _selected;
	bool _alive;

	PieceInputComponent* _input;
	PieceGraphicsComponent* _graphics;



};

