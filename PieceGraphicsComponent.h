#pragma once
#include "IDrawable.h"
#include "Texture.h"

class PieceGraphicsComponent :  public IDrawable
{
private:

	std::unique_ptr<Texture> _textureLoader;

	SDL_Texture* _selectedTexture;
	SDL_Texture* _pieceTexture;

	std::string _imgPath;

public:

	PieceGraphicsComponent();
	~PieceGraphicsComponent();

	void setImgPath(std::string path);

	void loadTexture();

	PieceGraphicsComponent* getGraphicsComponent();

	void addSelectedIcon();
	void removeSelectedIcon();
};

