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
	~Piece();

	Piece(const Piece& piece);
	Piece& operator=(const Piece& other);

	Piece(Piece&& piece) noexcept;
	Piece& operator=(Piece&& piece) noexcept;

	char const getFenName() const;

	/// <summary>
	/// Moves the piece.
	/// </summary>
	/// <param name="square">The square to move to.</param>
	void setSquare(Square* square = nullptr);

	Square* getSquare() const;

	inline const PieceColor getPieceColor() const { return _pieceColor; };
	inline const Figure getPieceType() const { return _type; };

	void changeType(const Figure& type);

	void setSelected(bool selected);
	inline bool getSelected() const { return _selected; };

	void setAlive(bool alive);
	inline bool isAlive() const { return _alive; };

	inline void setFirstMove(bool first) { _firstMove = first; };
	inline bool getFirstMove() const { return _firstMove; };

	inline void setPassantable(bool p) { _passantable = p; };
	inline bool getPassantable() { return _passantable; };

	inline PieceInputComponent* getInput() { return _input.get(); };
	inline PieceGraphicsComponent* getGraphics() { return _graphics.get(); };

private:

	void setFenName(char fen);
	
	Square* _position;
	PieceColor _pieceColor;
	Figure _type;
	char _fenName;
	bool _firstMove;
	// Can the piece be captured en passant? 
	// Should only be true just after its first move, if it moved two squares on that move.
	bool _passantable;
	bool _selected;
	bool _alive;

	std::unique_ptr<PieceInputComponent> _input;
	std::unique_ptr<PieceGraphicsComponent> _graphics;



};

