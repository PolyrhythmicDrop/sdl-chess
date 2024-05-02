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





