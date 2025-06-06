#include "GameObject.h"
#include "easylogging++.h"

GameObject::GameObject(std::string name, IMediator* mediator) :
	_mediator(mediator),
	_name(name),
	_dimensions({0, 0, 0, 0})
{
	gameObjectCount++;
	LOG(TRACE) << "Object " << _name << " created! Game object count: " << gameObjectCount;
}

GameObject::~GameObject()
{
	gameObjectCount--;
	LOG(TRACE) << "Object " << _name << " destroyed! Game object count : " << gameObjectCount;
}

void GameObject::setMediator(IMediator* mediator)
{
	_mediator = mediator;
}

const std::string& GameObject::getName() const
{
	return _name;
}

void GameObject::setName(const std::string& name) 
{ 
	_name = name;
}

const SDL_Rect* GameObject::getDimensions() const 
{
	return &_dimensions;
}

void GameObject::setScale(int w, int h)
{
	_dimensions.w = w;
	_dimensions.h = h;
}

int GameObject::getWidth() const
{
	return _dimensions.w;
}

int GameObject::getHeight() const
{
	return _dimensions.h;
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





