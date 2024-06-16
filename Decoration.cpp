#include "Decoration.h"
#include "easylogging++.h"

Decoration::Decoration(DecorationType type)	:
	_graphics(std::make_unique<GraphicsComponent>())
{
	switch (type)
	{
	case ESC_MENU_BG:
		_name = "Esc Menu Background";
		_graphics->setImgPath("images/esc-menu_bg-esc-menu.png");
		break;
	case RESO_MENU_BG:
		_name = "Resolution Menu Background";
		_graphics->setImgPath("images/esc-menu_bg-resolution-menu.png");
		break;
	case EXIT_CONFIRM_BG:
		_name = "Exit Confirmation Menu Background";
		_graphics->setImgPath("images/exit-confirm-menu_ConfirmExitBG.png");
		break;
	}
	_graphics->_draw = true;
	// Load the texture using the image path in the constructor's switch statement
	_graphics->loadTexture();
	// Set the initial dimensions for the decoration using the texture
	setScaleFromTexture(_graphics->getCurrentTexture());
	LOG(TRACE) << "Decoration " << _name << " created!";
}

Decoration::~Decoration()
{
	LOG(TRACE) << _name << " destructed!";
}

GraphicsComponent* Decoration::getGraphicsComponent()
{
	return _graphics.get()->getGraphicsComponent();
}



