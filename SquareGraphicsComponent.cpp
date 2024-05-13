#pragma once
#include "SquareGraphicsComponent.h"
#include "easylogging++.h"

SquareGraphicsComponent::SquareGraphicsComponent() :
	_squareImgPath(""),
	_overlayImgPath(""),
	_textureLoader(new Texture()),
	_sdlTexture(NULL),
	_squareTexture(NULL),
	_overlayTexture(NULL)
{
	LOG(INFO) << "Square graphics component constructed!";
}

SquareGraphicsComponent::~SquareGraphicsComponent()
{
	_textureLoader->~Texture();
	LOG(INFO) << "Square graphics component destructed!";
}

void SquareGraphicsComponent::loadTexture()
{
	_sdlTexture = SDL_CreateTexture(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, 125, 125);
	_squareTexture = _textureLoader->loadTextureFromImage(_squareImgPath);
	_overlayTexture = _textureLoader->loadTextureFromImage(_overlayImgPath);
}

SDL_Texture* SquareGraphicsComponent::getSquareTexture()
{
	return _squareTexture;
}

SDL_Texture* SquareGraphicsComponent::getOverlayTexture()
{
	return _overlayTexture;
}

void SquareGraphicsComponent::setSquareImgPath(std::string path)
{
	_squareImgPath = path;
}

void SquareGraphicsComponent::setOverlayImgPath(std::string path)
{
	_overlayImgPath = path;
}

void SquareGraphicsComponent::sumImage(Square* square)
{
	// Set the sum texture as the render target
	SDL_SetRenderTarget(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), _sdlTexture);

	// Clear the sum texture
	SDL_SetRenderDrawColor(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), 255, 255, 255, 255);
	SDL_RenderClear(ServiceLocator::getGraphics().getRenderer()->GetRenderer());
	// Set the blend mode for the sum texture
	SDL_SetTextureBlendMode(_sdlTexture, SDL_BLENDMODE_NONE);
	SDL_SetTextureAlphaMod(_sdlTexture, 255);

	// Set the blend mode for the tile texture
	SDL_SetTextureBlendMode(_squareTexture, SDL_BLENDMODE_NONE);
	SDL_SetTextureAlphaMod(_squareTexture, 255);
	// Set the color for light and dark squares

	if (square->getTileType() == Square::DARK)
	{
		SDL_SetTextureColorMod(_squareTexture, square->getDarkTileColor()->r, square->getDarkTileColor()->g, square->getDarkTileColor()->b);
	}
	else if (square->getTileType() == Square::LIGHT)
	{
		SDL_SetTextureColorMod(_squareTexture, square->getLightTileColor()->r, square->getLightTileColor()->g, square->getLightTileColor()->b);
	}

	SDL_RenderCopy(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), _squareTexture, NULL, NULL);

	SDL_SetTextureBlendMode(_overlayTexture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(_overlayTexture, 200);
	// Overlay color setting
	switch (square->getOverlayType())
	{
	case Square::NONE:
		SDL_SetTextureAlphaMod(_overlayTexture, 0);
		break;
	case Square::MOVE:
		SDL_SetTextureColorMod(_overlayTexture, square->getMoveOverlayColor()->r, square->getMoveOverlayColor()->g, square->getMoveOverlayColor()->b);
		break;
	case Square::TAKE:
		SDL_SetTextureColorMod(_overlayTexture, square->getTakeOverlayColor()->r, square->getTakeOverlayColor()->g, square->getTakeOverlayColor()->b);		
		break;
	}
	SDL_RenderCopy(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), _overlayTexture, NULL, NULL);	
	
	// Set the render target back to the window
	SDL_SetRenderTarget(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), NULL);
}

SDL_Texture* SquareGraphicsComponent::getSdlTexture()
{
	return _sdlTexture;
}

SquareGraphicsComponent* SquareGraphicsComponent::getGraphicsComponent()
{
	return this;
}
