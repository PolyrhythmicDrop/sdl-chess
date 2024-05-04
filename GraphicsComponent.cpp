#include "GraphicsComponent.h"

GraphicsComponent::GraphicsComponent() :
	_imgPath(""), _textureLoader(NULL), _sdlTexture(NULL), _zIndex(0)
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

int GraphicsComponent::getZ()
{
	return _zIndex;
}

void GraphicsComponent::setZ(int z)
{
	_zIndex = z;
}
