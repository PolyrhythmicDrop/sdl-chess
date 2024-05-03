#include "Decoration.h"

Decoration::Decoration(DecorationType type)	
{
	switch (type)
	{
	case ESC_MENU_BG:
		_name = "Esc Menu Background";
		_imgPath = "esc-menu_bg-esc-menu.png";
		break;
	case RESO_MENU_BG:
		_name = "Resolution Menu Background";
		_imgPath = "esc-menu_bg-resolution-menu.png";
		break;
	}
	std::cout << "Decoration " << _name << " created!\n";
}

Decoration::~Decoration()
{
	std::cout << _name << " destructed!\n";
}



