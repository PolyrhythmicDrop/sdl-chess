#include "GraphicsComponent.h"

GraphicsComponent::GraphicsComponent() :
	_imgPath(""), _textureLoader(NULL), _sdlTexture(NULL)
{
	_textureLoader = new Texture();
	std::cout << "Graphics component constructed!\n";
}

GraphicsComponent::~GraphicsComponent()
{
	_textureLoader->~Texture();
	std::cout << "Graphics component destructed!\n";
}

void GraphicsComponent::loadTexture()
{
	_sdlTexture = _textureLoader->loadTextureFromImage(_imgPath);
}

SDL_Texture* GraphicsComponent::getSdlTexture()
{
	return _sdlTexture;
}

GraphicsComponent* GraphicsComponent::getGraphicsComponent()
{
	return this;
}
