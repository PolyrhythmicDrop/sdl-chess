#pragma once
#include "GameObject.h"
#include "PieceInputComponent.h"
#include "GraphicsComponent.h"
#include <memory>

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

	std::unique_ptr<PieceInputComponent> _input;
	std::unique_ptr<GraphicsComponent> _graphics;

public:

	Piece(Figure type, PieceColor color);
	~Piece();

	inline void setPosition(Square* square) { _position = square; };
	inline Square* getPosition() { return _position; };

	inline const PieceColor getPieceColor() const { return _pieceColor; };

	void changeType(Figure type);

	inline void setSelected(bool selected) { _selected = selected; };
	inline bool getSelected() const { return _selected; };

	inline void setAlive(bool alive) { _alive = alive; };
	inline bool isAlive() const { return _alive; };

	inline PieceInputComponent* getInput() { return _input.get(); };
	inline GraphicsComponent* getGraphics() { return _graphics.get(); };



};

