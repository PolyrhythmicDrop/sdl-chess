#include "Button.h""

// Constructor, initialize values
Button::Button(std::string name, std::string imgPath) :
	GameObject::GameObject(name), IDrawable::IDrawable(imgPath)
{
	std::cout << "Button " << _name << " created!";
}

Button::~Button()
{
	std::cout << "Button " << _name << " destructed!";
}

void Button::onClick()
{
	// Do something when clicked
}