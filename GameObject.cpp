#include "GameObject.h"

GameObject::GameObject(std::string name) :
	_name(name),
	_dimensions({0, 0, 0, 0})
{
	gameObjectCount++;
	std::cout << "Object created! Game object count: " << gameObjectCount << "\n";
}

GameObject::~GameObject()
{
	gameObjectCount--;
	std::cout << "Object destroyed! Game object count: " << gameObjectCount << "\n";
}

std::string GameObject::getName()
{
	return _name;
}

GameObject::dim GameObject::getDimensions()
{
	return _dimensions;
}

void GameObject::setDimensions(int x, int y, int w, int h)
{
	_dimensions = { x, y, w, h };
}

void GameObject::setDimensionsFromTexture(SDL_Texture* texture)
{
	int w;
	int h;
	// Query loaded texture to get the width and height of the texture and set them to w & h variables
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	this->setDimensions(_dimensions.x, _dimensions.y, w, h);
}





