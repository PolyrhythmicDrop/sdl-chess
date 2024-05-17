#include "GraphicsComponent.h"
#include "easylogging++.h"

GraphicsComponent::GraphicsComponent() :
	_imgPath(""), _textureLoader(NULL), _sdlTexture(NULL)
{
	_textureLoader = new Texture();
	LOG(TRACE) << "Graphics component constructed!";
}

GraphicsComponent::~GraphicsComponent()
{
	_textureLoader->~Texture();
	LOG(TRACE) << "Graphics component destructed!";
}

void GraphicsComponent::loadTexture()
{
	_sdlTexture = _textureLoader->loadTextureFromImage(_imgPath);
}

void GraphicsComponent::setImgPath(std::string path)
{
	_imgPath = path;
}

SDL_Texture* GraphicsComponent::getSdlTexture()
{
	return _sdlTexture;
}

GraphicsComponent* GraphicsComponent::getGraphicsComponent()
{
	return this;
}
