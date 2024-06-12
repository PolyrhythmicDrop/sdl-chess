#include "GraphicsComponent.h"
#include "easylogging++.h"

GraphicsComponent::GraphicsComponent() :
	_imgPath(""),
	_textureLoader(std::make_unique<Texture>())	
{
	LOG(TRACE) << "Graphics component constructed!";
}

GraphicsComponent::~GraphicsComponent()
{
	_textureLoader->~Texture();
	LOG(TRACE) << "Graphics component destructed!";
}

void GraphicsComponent::loadTexture()
{
	 _currentTexture = _textureLoader->loadTextureFromImage(_imgPath);
	 setDrawScaleByTexture();
}

void GraphicsComponent::setImgPath(std::string path)
{
	_imgPath = path;
}

GraphicsComponent* GraphicsComponent::getGraphicsComponent()
{
	return this;
}
