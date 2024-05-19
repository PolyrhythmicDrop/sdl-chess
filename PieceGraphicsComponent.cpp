#include "PieceGraphicsComponent.h"
#include "easylogging++.h"
#include "Piece.h"

PieceGraphicsComponent::PieceGraphicsComponent() :
	_imgPath(""), 
	_textureLoader(NULL),
	_sdlTexture(NULL),
	_pieceTexture(NULL),
	_selectedTexture(NULL)
{
	_textureLoader = new Texture();
	_selectedTexture = _textureLoader->loadTextureFromImage("images/selected.png");
	LOG(TRACE) << "Piece graphics component constructed!";
}

PieceGraphicsComponent::~PieceGraphicsComponent()
{
	_textureLoader->~Texture();
	LOG(TRACE) << "Piece graphics component destructed!";
}

void PieceGraphicsComponent::loadTexture()
{
	_pieceTexture = _textureLoader->loadTextureFromImage(_imgPath);
	_sdlTexture = _pieceTexture;
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

void PieceGraphicsComponent::addSelectedIcon(Piece* piece)
{

}
