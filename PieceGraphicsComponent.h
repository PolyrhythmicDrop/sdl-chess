#pragma once
#include "IDrawable.h"
#include "Texture.h"

class Piece;

class PieceGraphicsComponent :  public IDrawable
{
private:
	Texture* _textureLoader;
	SDL_Texture* _sdlTexture;
	SDL_Texture* _selectedTexture;
	SDL_Texture* _pieceTexture;
	std::string _imgPath;

public:

	PieceGraphicsComponent();

	~PieceGraphicsComponent();

	void setImgPath(std::string path);

	void loadTexture();
	void loadTexture(Piece* piece);

	SDL_Texture* getSdlTexture();

	PieceGraphicsComponent* getGraphicsComponent();

	void addSelectedIcon(Piece* piece);
	void removeSelectedIcon(Piece* piece);
};

