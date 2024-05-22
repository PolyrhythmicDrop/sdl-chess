#include "GameObject.h"
#include "easylogging++.h"

GameObject::GameObject(std::string name, IMediator* mediator) :
	_mediator(mediator),
	_name(name),
	_dimensions({0, 0, 0, 0}),
	_zIndex(0),
	_draw(false)
{
	gameObjectCount++;
	LOG(TRACE) << "Object created! Game object count: " << gameObjectCount;
}

GameObject::~GameObject()
{
	gameObjectCount--;
	LOG(TRACE) << "Object destroyed! Game object count: " << gameObjectCount;
}

void GameObject::setMediator(IMediator* mediator)
{
	this->_mediator = mediator;
}

std::string const GameObject::getName()
{
	return this->_name;
}

SDL_Rect* GameObject::getDimensions()
{
	return &_dimensions;
}

void GameObject::setScale(int w, int h)
{
	_dimensions.w = w;
	_dimensions.h = h;
}

int GameObject::getWidth()
{
	return _dimensions.w;
}

int GameObject::getHeight()
{
	return _dimensions.h;
}

int GameObject::getZ()
{
	return _zIndex;
}

void GameObject::setZ(int z)
{
	_zIndex = z;
}

void GameObject::setPosition(int x, int y)
{
	_dimensions.x = x;
	_dimensions.y = y;
}

void GameObject::setScaleFromTexture(SDL_Texture* texture)
{
	int w;
	int h;
	// Query loaded texture to get the width and height of the texture and set them to w & h variables
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);	
	this->setScale(w, h);
}





