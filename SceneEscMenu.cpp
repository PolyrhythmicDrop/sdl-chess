#include "SceneEscMenu.h"

SceneEscMenu::SceneEscMenu()
{
	
}

SceneEscMenu::~SceneEscMenu()
{

}

void SceneEscMenu::buildScene()
{
	// Instantiate the buttons and backgrounds	
	Decoration* escMenuBg = new Decoration(Decoration::ESC_MENU_BG);	
	Button* optionsButton = new Button(Button::OPTIONS);
	Button* backButton = new Button(Button::BACK);
	Button* exitButton = new Button(Button::EXIT_GAME);

	// Add the objects to the object array
	addObject(escMenuBg);
	addObject(optionsButton);
	addObject(backButton);
	addObject(exitButton);

	// Add all the object texture to a separate array; make sure they're in the same order they were added to the object array
	std::vector<SDL_Texture*> vTexture = 
	{
		escMenuBg->getSdlTexture(), 
		optionsButton->getSdlTexture(),
		backButton->getSdlTexture(),
		exitButton->getSdlTexture()
	};


	// Set the dimensions for each object according to its texture
	for (auto i = 0; i <= _objectVector.size(); i++)
	{
		_objectVector[i]->setDimensionsFromTexture(vTexture[i]);
	}
}