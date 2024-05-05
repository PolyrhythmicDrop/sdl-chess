#include "GameObject.h"

GameObject::GameObject(std::string name) :
	_name(name),
	_dimensions({0, 0, 0, 0}),
	_zIndex(0)
{
	GameContext::gameObjectCount++;
	std::cout << "Object created! Game object count: " << GameContext::gameObjectCount << "\n";
}

GameObject::~GameObject()
{
	GameContext::gameObjectCount--;
	std::cout << "Object destroyed! Game object count: " << GameContext::gameObjectCount << "\n";
}

std::string GameObject::getName()
{
	return _name;
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





