#include "Decoration.h"

Decoration::Decoration(std::string name, std::string path) :
	GameObject::GameObject(name), IDrawable::IDrawable(path)
{
	std::cout << "Decoration " << _name << " created!\n";
}

Decoration::~Decoration()
{
	std::cout << _name << " destructed!\n";
}



