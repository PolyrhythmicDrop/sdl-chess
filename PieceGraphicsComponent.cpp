#include "PieceGraphicsComponent.h"
#include "easylogging++.h"

PieceGraphicsComponent::PieceGraphicsComponent() :
	_imgPath(""), 
	_textureLoader(std::make_unique<Texture>()),
	_pieceTexture(nullptr),
	_selectedTexture(nullptr)
{
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
	Texture* selected{ new Texture() };
	_selectedTexture = selected->loadTextureFromImage("images/selected.png");

	int pieceW, pieceH;
	Uint32 format;
	SDL_QueryTexture(_pieceTexture, &format, NULL, &pieceW, &pieceH);

	_currentTexture = SDL_CreateTexture(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), format, SDL_TEXTUREACCESS_TARGET, pieceW, pieceH);
	if (!_currentTexture)
	{
		LOG(DEBUG) << SDL_GetError();
	}

	SDL_SetRenderTarget(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), _currentTexture);

	SDL_SetRenderDrawColor(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), 0, 0, 0, 0);
	SDL_SetRenderDrawBlendMode(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_RenderClear(ServiceLocator::getGraphics().getRenderer()->GetRenderer());

	SDL_SetTextureAlphaMod(_currentTexture, 255);
	SDL_SetTextureBlendMode(_currentTexture, SDL_BLENDMODE_BLEND);

	SDL_SetTextureAlphaMod(_pieceTexture, 255);
	SDL_SetTextureBlendMode(_pieceTexture, SDL_BLENDMODE_NONE);
	SDL_RenderCopy(ServiceLocator::getGraphics().getRenderer()->GetRenderer(),_pieceTexture, nullptr, nullptr);

	SDL_SetTextureScaleMode(_currentTexture, SDL_ScaleModeLinear);

	SDL_SetRenderTarget(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), nullptr);
}

void PieceGraphicsComponent::setImgPath(std::string path)
{
	_imgPath = path;
}

PieceGraphicsComponent* PieceGraphicsComponent::getGraphicsComponent()
{
	return this;
}

void PieceGraphicsComponent::addSelectedIcon()
{
	SDL_SetRenderTarget(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), _currentTexture);

	SDL_SetRenderDrawColor(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), 0, 0, 0, 0);
	SDL_SetRenderDrawBlendMode(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_RenderClear(ServiceLocator::getGraphics().getRenderer()->GetRenderer());

	SDL_SetTextureAlphaMod(_currentTexture, 255);
	SDL_SetTextureBlendMode(_currentTexture, SDL_BLENDMODE_BLEND);


	SDL_SetTextureAlphaMod(_pieceTexture, 255);
	SDL_SetTextureBlendMode(_pieceTexture, SDL_BLENDMODE_NONE);
	SDL_RenderCopy(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), _pieceTexture, nullptr, nullptr);

	SDL_SetTextureAlphaMod(_selectedTexture, 255);
	SDL_SetTextureBlendMode(_selectedTexture, SDL_BLENDMODE_BLEND);
	SDL_RenderCopy(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), _selectedTexture, nullptr, nullptr);

	SDL_SetRenderTarget(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), nullptr);
}

void PieceGraphicsComponent::removeSelectedIcon()
{
	SDL_SetRenderTarget(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), _currentTexture);

	SDL_SetRenderDrawColor(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), 0, 0, 0, 0);
	SDL_SetRenderDrawBlendMode(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_RenderClear(ServiceLocator::getGraphics().getRenderer()->GetRenderer());

	SDL_SetTextureAlphaMod(_currentTexture, 255);
	SDL_SetTextureBlendMode(_currentTexture, SDL_BLENDMODE_BLEND);


	SDL_SetTextureAlphaMod(_pieceTexture, 255);
	SDL_SetTextureBlendMode(_pieceTexture, SDL_BLENDMODE_NONE);
	SDL_RenderCopy(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), _pieceTexture, nullptr, nullptr);

	SDL_SetRenderTarget(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), nullptr);
}
