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
{}

void SquareGraphicsComponent::loadTexture(Square* square)
{
	_sdlTexture = SDL_CreateTexture(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, square->getDimensions()->w, square->getDimensions()->h);
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

	// Set the blend mode for the square texture
	SDL_SetTextureBlendMode(_squareTexture, SDL_BLENDMODE_NONE);
	// Set the color for light and dark squares
	switch (square->getTileType())
	{
	case Square::DARK:
		SDL_SetRenderDrawColor(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), square->getDarkTileColor()->r, square->getDarkTileColor()->g, square->getDarkTileColor()->b, 255);
		SDL_RenderClear(ServiceLocator::getGraphics().getRenderer()->GetRenderer());

		break;
	case Square::LIGHT:
		SDL_SetRenderDrawColor(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), square->getLightTileColor()->r, square->getLightTileColor()->g, square->getLightTileColor()->b, 255);
		SDL_RenderClear(ServiceLocator::getGraphics().getRenderer()->GetRenderer());
		break;
	}
	

	// Overlay color setting
	switch (square->getOverlayType())
	{
	case Square::NONE:
		LOG(INFO) << "The name of this square is " << square->getName();
		SDL_SetTextureBlendMode(_overlayTexture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(_overlayTexture, 0);
		SDL_RenderCopy(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), _overlayTexture, NULL, NULL);
		break;
	case Square::MOVE:
		SDL_SetTextureBlendMode(_overlayTexture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(_overlayTexture, 200);
		SDL_SetTextureColorMod(_overlayTexture, square->getMoveOverlayColor()->r, square->getMoveOverlayColor()->g, square->getMoveOverlayColor()->b);
		SDL_RenderCopy(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), _overlayTexture, NULL, NULL);
		break;
	case Square::TAKE:
		SDL_SetTextureBlendMode(_overlayTexture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(_overlayTexture, 200);
		SDL_SetTextureColorMod(_overlayTexture, square->getTakeOverlayColor()->r, square->getTakeOverlayColor()->g, square->getTakeOverlayColor()->b);	
		SDL_RenderCopy(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), _overlayTexture, NULL, square->getDimensions());
		break;
	}
	// Render the square texture and the overlay texture to the sum texture
	
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
