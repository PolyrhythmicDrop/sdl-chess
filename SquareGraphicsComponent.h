#pragma once
#include "IDrawable.h"
#include "Texture.h"
#include "Square.h"

struct Color {
	Uint8 r, g, b, a;
};

class SquareGraphicsComponent : public IDrawable
{
private:
	Square* _square;

	std::unique_ptr<Texture> _textureLoader;

	SDL_Texture* _squareTexture;
	SDL_Texture* _overlayTexture;

	std::string _squareImgPath;
	std::string _overlayImgPath;

	Color _moveOverlayColor;
	Color _takeOverlayColor;

	Color _lightTileColor;
	Color _darkTileColor;

public:

	SquareGraphicsComponent(Square* square);
	~SquareGraphicsComponent();

	// IDrawable functions
	void loadTexture();
	void loadTexture(Square* square);

	// Get the textures for the overlay and the square to edit their colors individually
	SDL_Texture* getSquareTexture();
	SDL_Texture* getOverlayTexture();

	// Overlay Color functions
	inline const Color* getMoveOverlayColor() { return &_moveOverlayColor; };
	inline const Color* getTakeOverlayColor() { return &_takeOverlayColor; };
	void setMoveOverlayColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void setTakeOverlayColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	// Tile color functions

	inline const Color* getLightTileColor() const { return &_lightTileColor; };
	inline const Color* getDarkTileColor() const { return &_darkTileColor; };
	void setLightTileColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void setDarkTileColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	void setSquareImgPath(std::string path);
	void setOverlayImgPath(std::string path);

	// Combines the square texture and the overlay texture into a single texture for rendering
	void sumImage(Square* square);

	SquareGraphicsComponent* getGraphicsComponent();

};



