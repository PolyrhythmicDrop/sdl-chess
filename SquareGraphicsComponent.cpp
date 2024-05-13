#pragma once
#include "SquareGraphicsComponent.h"
#include "easylogging++.h"

SquareGraphicsComponent::SquareGraphicsComponent() :
	_squareImgPath(""),
	_overlayImgPath(""),
	_textureLoader(new Texture()),
	_sdlTexture(SDL_CreateTexture(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, 125, 125)),
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

void SquareGraphicsComponent::sumImage()
{
	// Set the sum texture as the render target
	SDL_SetRenderTarget(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), _sdlTexture);

	// Clear the sum texture
	SDL_SetRenderDrawColor(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), 255, 255, 255, 255);
	SDL_RenderClear(ServiceLocator::getGraphics().getRenderer()->GetRenderer());

	// Sum the overlay texture and the square texture into the sum texture
	SDL_RenderCopy(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), _squareTexture, NULL, NULL);
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
