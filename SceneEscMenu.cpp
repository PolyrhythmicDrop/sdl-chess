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
	
	// Set the Z-values
	escMenuBg->setZ(100);
	optionsButton->setZ(101);
	backButton->setZ(102);
	exitButton->setZ(103);

	// Set the positions
	escMenuBg->setPosition(	(windowW / 2) - (escMenuBg->getWidth() / 2), (windowH / 2) - (escMenuBg->getHeight() / 2) );

	optionsButton->setPosition((windowW / 2) - (optionsButton->getWidth() / 2), (escMenuBg->getDimensions()->y + (optionsButton->getHeight() / 2)));

	backButton->setPosition((windowW / 2) - (backButton->getWidth() / 2), ((escMenuBg->getDimensions()->y) + (escMenuBg->getHeight() / 2)) - (backButton->getHeight() / 2));

	exitButton->setPosition((windowW / 2) - (exitButton->getWidth() / 2), (escMenuBg->getDimensions()->y + escMenuBg->getHeight() - exitButton->getHeight()) - (exitButton->getHeight() / 2));

	// Add the objects to the scene map
	addObject(escMenuBg, escMenuBg->getGraphicsComponent()->getSdlTexture());
	addObject(optionsButton, optionsButton->getGraphicsComponent()->getSdlTexture());
	addObject(backButton, backButton->getGraphicsComponent()->getSdlTexture());
	addObject(exitButton, exitButton->getGraphicsComponent()->getSdlTexture());
	

	// Add the scene map to the render map in the Graphics Service
	ServiceLocator::getGraphics().addToRenderMap(_sceneMap);


}