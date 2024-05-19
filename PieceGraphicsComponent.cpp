#include "PieceGraphicsComponent.h"
#include "easylogging++.h"

PieceGraphicsComponent::PieceGraphicsComponent() :
	_imgPath(""), _textureLoader(NULL), _sdlTexture(NULL)
{
	_textureLoader = new Texture();
	LOG(TRACE) << "Piece graphics component constructed!";
}

PieceGraphicsComponent::~PieceGraphicsComponent()
{
	_textureLoader->~Texture();
	LOG(TRACE) << "Piece graphics component destructed!";
}

void PieceGraphicsComponent::loadTexture()
{
	_sdlTexture = _textureLoader->loadTextureFromImage(_imgPath);
	SDL_SetTextureScaleMode(_sdlTexture, SDL_ScaleModeLinear );
}

void PieceGraphicsComponent::setImgPath(std::string path)
{
	_imgPath = path;
}

SDL_Texture* PieceGraphicsComponent::getSdlTexture()
{
	return _sdlTexture;
}

PieceGraphicsComponent* PieceGraphicsComponent::getGraphicsComponent()
{
	return this;
}
