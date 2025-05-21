#include "Button.h"
#include "ButtonInputComponent.h"
#include "easylogging++.h"

// Constructor, initialize values
Button::Button(ButtonType bType) :
	_graphics(std::make_unique<GraphicsComponent>()),
	_input(std::make_unique<ButtonInputComponent>()), 
	type(bType)
{
	// Sets the button's name and texture path, depending on the type of button it is.
	switch (bType)
	{
		case OPTIONS:
			type = OPTIONS;
			_name = "Options Button";
			_graphics->setImgPath("assets/esc-menu_button-options.png");
			break;
		case BACK:
			type = BACK;
			_name = "Back Button";
			_graphics->setImgPath("assets/esc-menu_button-back.png");
			break;
		case EXITGAME:
			type = EXITGAME;
			_name = "Exit Game Button";
			_graphics->setImgPath("assets/esc-menu_button-exit.png");
			break;
		case RESOLUTION:
			type = RESOLUTION;
			_name = "Resolution Button";
			_graphics->setImgPath("assets/esc-menu_button-resolution.png");
			break;
		case TENTWENTYFOUR:
			type = TENTWENTYFOUR;
			_name = "1024x768";
			_graphics->setImgPath("assets/esc-menu_1024.png");
			break;
		case NINETEENTWENTY:
			type = NINETEENTWENTY;
			_name = "1920x1080";
			_graphics->setImgPath("assets/esc-menu_1920.png");
			break;
		case YES:
			type = YES;
			_name = "Yes Button";
			_graphics->setImgPath("assets/exit-confirm-menu_button-yes.png");
			break;
		case NO:
			type = NO;
			_name = "No Button";
			_graphics->setImgPath("assets/exit-confirm-menu_button-no.png");
			break;
	}
	_graphics->loadTexture();
	_graphics->_draw = true;

	// Set object dimensions (NOT draw dimensions)
	setScaleFromTexture(_graphics->getCurrentTexture());

	LOG(TRACE) << "Button " << _name << " created!";
}

Button::~Button()
{
	LOG(TRACE) << "Button " << _name << " destructed!";
}

GraphicsComponent* Button::getGraphicsComponent()
{
	return _graphics.get()->getGraphicsComponent();
}

ButtonInputComponent* Button::getInputComponent()
{
	return _input.get();
}