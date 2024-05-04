#include "Decoration.h"

Decoration::Decoration(DecorationType type)	:
	_graphics(new GraphicsComponent())
{
	switch (type)
	{
	case ESC_MENU_BG:
		_name = "Esc Menu Background";
		_graphics->_imgPath = "esc-menu_bg-esc-menu.png";
		break;
	case RESO_MENU_BG:
		_name = "Resolution Menu Background";
		_graphics->_imgPath = "esc-menu_bg-resolution-menu.png";
		break;
	}
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



