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

	// Get window variables
	int windowW;
	int windowH;
	ServiceLocator::getGraphics().getWindow()->getWindowSize(&windowW, &windowH);
	// Position the objects
	


	// Add the objects to the scene map
	addObject(escMenuBg, escMenuBg->getGraphicsComponent()->getSdlTexture());
	addObject(optionsButton, optionsButton->getGraphicsComponent()->getSdlTexture());
	addObject(backButton, backButton->getGraphicsComponent()->getSdlTexture());
	addObject(exitButton, exitButton->getGraphicsComponent()->getSdlTexture());	

	// Debug to make sure this is actually happening
	std::map<GameObject*, SDL_Texture*>::iterator itr;
	for (itr = _sceneMap.begin(); itr != _sceneMap.end(); ++itr)
	{
		std::cout << "Object name " << itr->first->getName() << " has been inserted into the scene map!\n";
	}

	// Add the scene map to the render map in the Graphics Service
	ServiceLocator::getGraphics().addToRenderMap(_sceneMap);


}