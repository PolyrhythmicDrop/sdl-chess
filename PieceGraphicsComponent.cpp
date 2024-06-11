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
	LOG(TRACE) << "Piece graphics component constructed!";
}

PieceGraphicsComponent::~PieceGraphicsComponent()
{
	_textureLoader->~Texture();
	LOG(TRACE) << "Piece graphics component destructed!";
}

void PieceGraphicsComponent::loadTexture()
{
	
}

void PieceGraphicsComponent::loadTexture(Piece* piece)
{
	this->_pieceTexture = _textureLoader->loadTextureFromImage(_imgPath);
	Texture* selected{new Texture()};
	_selectedTexture = selected->loadTextureFromImage("images/selected.png");

	int pieceW, pieceH;
	Uint32 format;
	SDL_QueryTexture(_pieceTexture, &format, NULL, &pieceW, &pieceH);

	_sdlTexture = SDL_CreateTexture(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), format, SDL_TEXTUREACCESS_TARGET, pieceW, pieceH);
	if (_sdlTexture == NULL)
	{
		LOG(DEBUG) << SDL_GetError();
	}

	SDL_SetRenderTarget(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), piece->getGraphics()->_sdlTexture);

	SDL_SetRenderDrawColor(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), 0, 0, 0, 0);
	SDL_SetRenderDrawBlendMode(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_RenderClear(ServiceLocator::getGraphics().getRenderer()->GetRenderer());
	
	SDL_SetTextureAlphaMod(piece->getGraphics()->_sdlTexture, 255);
	SDL_SetTextureBlendMode(piece->getGraphics()->_sdlTexture, SDL_BLENDMODE_BLEND);

	SDL_SetTextureAlphaMod(piece->getGraphics()->_pieceTexture, 255);
	SDL_SetTextureBlendMode(piece->getGraphics()->_pieceTexture, SDL_BLENDMODE_NONE);
	SDL_RenderCopy(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), piece->getGraphics()->_pieceTexture, NULL, NULL);
	
	SDL_SetTextureScaleMode(_sdlTexture, SDL_ScaleModeLinear);

	SDL_SetRenderTarget(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), NULL);
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
	SDL_SetRenderTarget(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), piece->getGraphics()->_sdlTexture);

	SDL_SetRenderDrawColor(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), 0, 0, 0, 0);
	SDL_SetRenderDrawBlendMode(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_RenderClear(ServiceLocator::getGraphics().getRenderer()->GetRenderer());

	SDL_SetTextureAlphaMod(piece->getGraphics()->_sdlTexture, 255);
	SDL_SetTextureBlendMode(piece->getGraphics()->_sdlTexture, SDL_BLENDMODE_BLEND);


	SDL_SetTextureAlphaMod(piece->getGraphics()->_pieceTexture, 255);
	SDL_SetTextureBlendMode(piece->getGraphics()->_pieceTexture, SDL_BLENDMODE_NONE);
	SDL_RenderCopy(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), piece->getGraphics()->_pieceTexture, NULL, NULL);

	SDL_SetTextureAlphaMod(piece->getGraphics()->_selectedTexture, 255);
	SDL_SetTextureBlendMode(piece->getGraphics()->_selectedTexture, SDL_BLENDMODE_BLEND);
	SDL_RenderCopy(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), piece->getGraphics()->_selectedTexture, NULL, NULL);

	SDL_SetRenderTarget(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), NULL);
}

void PieceGraphicsComponent::removeSelectedIcon(Piece* piece)
{
	SDL_SetRenderTarget(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), piece->getGraphics()->_sdlTexture);

	SDL_SetRenderDrawColor(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), 0, 0, 0, 0);
	SDL_SetRenderDrawBlendMode(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_RenderClear(ServiceLocator::getGraphics().getRenderer()->GetRenderer());

	SDL_SetTextureAlphaMod(piece->getGraphics()->_sdlTexture, 255);
	SDL_SetTextureBlendMode(piece->getGraphics()->_sdlTexture, SDL_BLENDMODE_BLEND);


	SDL_SetTextureAlphaMod(piece->getGraphics()->_pieceTexture, 255);
	SDL_SetTextureBlendMode(piece->getGraphics()->_pieceTexture, SDL_BLENDMODE_NONE);
	SDL_RenderCopy(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), piece->getGraphics()->_pieceTexture, NULL, NULL);

	SDL_SetRenderTarget(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), NULL);
}
