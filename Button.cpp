#include "Button.h"

// Constructor, initialize values
Button::Button(ButtonType type) :
	_graphics(new GraphicsComponent())

{
	// Sets the button's name and texture path, depending on the type of button it is.
	switch (type)
	{
		case OPTIONS:
			_name = "Options Button";
			_graphics->_imgPath = "images/esc-menu_button-options.png";
			break;
		case BACK:
			_name = "Back Button";
			_graphics->_imgPath = "images/esc-menu_button-back.png";
			break;
		case EXIT_GAME:
			_name = "Exit Game Button";
			_graphics->_imgPath = "images/esc-menu_button-exit.png";
			break;
		case RESOLUTION:
			_name = "Resolution Button";
			_graphics->_imgPath = "images/esc-menu_button-resolution.png";
			break;
	}
	_graphics->loadTexture();		
	std::cout << "Button " << _name << " created!\n";
}

Button::~Button()
{
	std::cout << "Button " << _name << " destructed!\n";
}

GraphicsComponent* Button::getGraphicsComponent()
{
	return _graphics->getGraphicsComponent();
}