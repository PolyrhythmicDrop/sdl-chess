#include "Decoration.h"

Decoration::Decoration(std::string name, std::string path) :
	GameObject::GameObject(name), IDrawable::IDrawable(path)
{
	
}

Decoration::~Decoration()
{
	std::cout << _name << " destructed!\n";
}

void Decoration::loadTexture()
{
	_texture->loadTextureFromImage(_imgPath);
	std::cout << "Texture loaded to " << _name << "!\n";
}

void Decoration::addToDrawQueue(GraphicsService* dm)
{
	
}

void Decoration::draw(GraphicsService* dm)
{
	
}



