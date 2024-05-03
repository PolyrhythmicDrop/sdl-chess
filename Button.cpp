#include "Button.h""

// Constructor, initialize values
Button::Button(ButtonType type)
{
	// Sets the button's name and texture path, depending on the type of button it is.
	switch (type)
	{
		case OPTIONS:
			_name = "Options Button";
			_imgPath = "esc-menu_button-options.png";
			break;
		case BACK:
			_name = "Back Button";
			_imgPath = "esc-menu_button-back.png";
			break;
		case EXIT_GAME:
			_name = "Exit Game Button";
			_imgPath = "esc-menu_button-exit.png";
			break;
		case RESOLUTION:
			_name = "Resolution Button";
			_imgPath = "esc-menu_button-resolution.png";
	}
		
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