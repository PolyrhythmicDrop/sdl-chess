#pragma once
#include "IDrawable.h"
#include "Texture.h"
#include "Square.h"

class SquareGraphicsComponent : public IDrawable
{
private:
	Texture* _textureLoader;

	SDL_Texture* _sdlTexture;
	SDL_Texture* _squareTexture;
	SDL_Texture* _overlayTexture;

	std::string _squareImgPath;
	std::string _overlayImgPath;

public:

	SquareGraphicsComponent();
	~SquareGraphicsComponent();

	// IDrawable functions

	void loadTexture();
	SDL_Texture* getSdlTexture();

	// Get the textures for the overlay and the square to edit their colors individually
	SDL_Texture* getSquareTexture();
	SDL_Texture* getOverlayTexture();

	void setSquareImgPath(std::string path);
	void setOverlayImgPath(std::string path);

	// Combines the square texture and the overlay texture into a single texture for rendering
	void sumImage(Square* square);

	SquareGraphicsComponent* getGraphicsComponent();

};



