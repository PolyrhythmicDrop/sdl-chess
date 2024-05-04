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
	// Set the Z-values
	escMenuBg->setZ(0);
	optionsButton->setZ(1);
	backButton->setZ(2);
	exitButton->setZ(3);

	// Set the position
	escMenuBg->setPosition(	(windowW / 2) - (escMenuBg->getWidth() / 2), (windowH / 2) - (escMenuBg->getHeight() / 2) );

	optionsButton->setPosition((windowW / 2) - (optionsButton->getWidth() / 2), (escMenuBg->getDimensions()->y + optionsButton->getHeight()));

	backButton->setPosition((windowW / 2) - (backButton->getWidth() / 2), (optionsButton->getDimensions()->y + backButton->getHeight()));

	exitButton->setPosition((windowW / 2) - (exitButton->getWidth() / 2), (backButton->getDimensions()->y + exitButton->getHeight()));

	// Add the objects to the scene map
	addObject(escMenuBg, escMenuBg->getGraphicsComponent()->getSdlTexture());
	addObject(optionsButton, optionsButton->getGraphicsComponent()->getSdlTexture());
	addObject(backButton, backButton->getGraphicsComponent()->getSdlTexture());
	addObject(exitButton, exitButton->getGraphicsComponent()->getSdlTexture());

	// Debug to make sure this is actually happening
	std::map<int, std::pair<GameObject*, SDL_Texture*>>::iterator sceneItr = _sceneMap.begin();	
	// Now the real test begins
	for (sceneItr = _sceneMap.begin(); sceneItr != _sceneMap.end(); ++sceneItr)
	{
		std::cout << "The first item in the scene map is named " << sceneItr->second.first->getName() << ", and its Z-value is " << sceneItr->second.first->getZ() << ".\nHopefully this matches with its map key, which is " << sceneItr->first << "\n";
	}


	std::cout << "Esc Menu Z: " << escMenuBg->getZ() << "\n"
		<< "Options Z: " << optionsButton->getZ() << "\n"
		<< "Back Z: " << backButton->getZ() << "\n"
		<< "Exit Z: " << exitButton->getZ() << "\n";
	

	// Add the scene map to the render map in the Graphics Service
	ServiceLocator::getGraphics().addToRenderMap(_sceneMap);


}