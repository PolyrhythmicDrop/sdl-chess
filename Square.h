#pragma once
#include "GameObject.h"
#include "GraphicsComponent.h"

// class SquareGraphicsComponent;

struct Color {
	Uint8 r, g, b, a;
};

// A square on the chessboard.
class Square : public GameObject
{

private:
	Color _moveOverlayColor;
	Color _takeOverlayColor;
	GraphicsComponent* _graphics;

	enum Overlay {
		NONE,
		MOVE,
		TAKE
	};

	Overlay _overlay;

public:
	// True if the square is occupied, false if empty. If occupied, the square will use the take overlay. If empty, the square will use the move overlay.
	bool _occupied;

	Square(std::string name);
	~Square();

	// inline SquareGraphicsComponent* getGraphics() { return _graphics; };
	GraphicsComponent* getGraphicsComponent();

	inline void setOccupied(bool occupied) { _occupied = occupied; };

	inline const Color* getMoveOverlayColor() { return &_moveOverlayColor; };
	inline const Color* getTakeOverlayColor() { return &_takeOverlayColor; };
	void setMoveOverlayColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void setTakeOverlayColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	void setOverlayType(Overlay overlay);

	// void drawOverlay();



};

