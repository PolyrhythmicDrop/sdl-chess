#include "Decoration.h"

Decoration::Decoration(DecorationType type)	:
	_graphics(new GraphicsComponent())
{
	switch (type)
	{
	case ESC_MENU_BG:
		_name = "Esc Menu Background";
		_graphics->_imgPath = "images/esc-menu_bg-esc-menu.png";		
		break;
	case RESO_MENU_BG:
		_name = "Resolution Menu Background";
		_graphics->_imgPath = "images/esc-menu_bg-resolution-menu.png";
		break;
	}
	// Load the texture using the image path in the constructor's switch statement
	_graphics->loadTexture();
	// Set the initial dimensions for the decoration using the texture
	setScaleFromTexture(_graphics->getSdlTexture());
	std::cout << "Decoration " << _name << " created!\n";
}

Decoration::~Decoration()
{
	std::cout << _name << " destructed!\n";
}

GraphicsComponent* Decoration::getGraphicsComponent()
{
	return _graphics->getGraphicsComponent();
}



