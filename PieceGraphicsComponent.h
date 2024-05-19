#pragma once
#include "IDrawable.h"
#include "Texture.h"

class PieceGraphicsComponent :  public IDrawable
{
private:
	Texture* _textureLoader;
	SDL_Texture* _sdlTexture;
	std::string _imgPath;

public:

	PieceGraphicsComponent();

	~PieceGraphicsComponent();

	void setImgPath(std::string path);

	void loadTexture();

	SDL_Texture* getSdlTexture();

	PieceGraphicsComponent* getGraphicsComponent();
};

