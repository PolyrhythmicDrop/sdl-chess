#pragma once
#include "SquareGraphicsComponent.h"
#include "easylogging++.h"

SquareGraphicsComponent::SquareGraphicsComponent(Square* square) :
	_square(square),
	_squareImgPath(""),
	_overlayImgPath(""),
	_textureLoader(std::make_unique<Texture>()),
	_moveOverlayColor({ 81, 224, 240, 255 }),
	_takeOverlayColor({ 240, 121, 81, 255 }),
	_lightTileColor({ 255, 245, 207, 255 }),
	_darkTileColor({ 143, 132, 89, 255 }),
	_squareTexture(nullptr),
	_overlayTexture(nullptr)
{
	_zIndex = 1;
	_drawDimensions = { square->getDimensions()->x, square->getDimensions()->y, square->getDimensions()->w, square->getDimensions()->h };
	LOG(INFO) << "Square graphics component constructed!";
}

SquareGraphicsComponent::~SquareGraphicsComponent()
{
	LOG(INFO) << "Square graphics component destructed!";
}

void SquareGraphicsComponent::loadTexture()
{}

void SquareGraphicsComponent::loadTexture(Square* square)
{
	_currentTexture = SDL_CreateTexture(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, square->getDimensions()->w, square->getDimensions()->h);
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

void SquareGraphicsComponent::setMoveOverlayColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	_moveOverlayColor = { r, g, b, a };
	sumImage(_square);
}

void SquareGraphicsComponent::setTakeOverlayColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	_takeOverlayColor = { r, g, b, a };
	sumImage(_square);
}

void SquareGraphicsComponent::setLightTileColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	_lightTileColor = { r, g, b, a };
	sumImage(_square);
}

void SquareGraphicsComponent::setDarkTileColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	_darkTileColor = { r, g, b, a };
	sumImage(_square);
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
	SDL_SetRenderTarget(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), _currentTexture);

	// Clear the sum texture
	SDL_SetRenderDrawColor(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), 255, 255, 255, 255);
	SDL_RenderClear(ServiceLocator::getGraphics().getRenderer()->GetRenderer());

	// Set the blend mode for the sum texture
	SDL_SetTextureBlendMode(_currentTexture, SDL_BLENDMODE_NONE);
	SDL_SetTextureAlphaMod(_currentTexture, 255);

	// Set the blend mode for the square texture
	SDL_SetTextureBlendMode(_squareTexture, SDL_BLENDMODE_NONE);
	// Set the color for light and dark squares
	switch (square->getTileType())
	{
	case Square::DARK:
		SDL_SetRenderDrawColor(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), _darkTileColor.r, _darkTileColor.g, _darkTileColor.b, 255);
		SDL_RenderClear(ServiceLocator::getGraphics().getRenderer()->GetRenderer());
		break;
	case Square::LIGHT:
		SDL_SetRenderDrawColor(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), _lightTileColor.r, _lightTileColor.g, _lightTileColor.b, 255);
		SDL_RenderClear(ServiceLocator::getGraphics().getRenderer()->GetRenderer());
		break;
	}
	
	// Overlay color setting
	switch (square->getOverlayType())
	{
	case Square::NONE:
	case Square::CHECK:
		SDL_SetTextureBlendMode(_overlayTexture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(_overlayTexture, 0);
		SDL_RenderCopy(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), _overlayTexture, nullptr, nullptr);
		break;
	case Square::MOVE:
	case Square::CASTLE:
		SDL_SetTextureBlendMode(_overlayTexture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(_overlayTexture, 200);
		SDL_SetTextureColorMod(_overlayTexture, _moveOverlayColor.r, _moveOverlayColor.g, _moveOverlayColor.b);
		SDL_RenderCopy(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), _overlayTexture, nullptr, nullptr);
		break;
	case Square::TAKE:
		SDL_SetTextureBlendMode(_overlayTexture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(_overlayTexture, 200);
		SDL_SetTextureColorMod(_overlayTexture, _takeOverlayColor.r, _takeOverlayColor.g, _takeOverlayColor.b);
		SDL_RenderCopy(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), _overlayTexture, nullptr, nullptr);
		break;
	}
	// Render the square texture and the overlay texture to the sum texture
	
	// Set the render target back to the window
	SDL_SetRenderTarget(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), nullptr);
}

SquareGraphicsComponent* SquareGraphicsComponent::getGraphicsComponent()
{
	return this;
}
