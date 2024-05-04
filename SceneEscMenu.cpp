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

	// Add the objects to the scene map
	addObject(escMenuBg, escMenuBg->getGraphicsComponent()->getSdlTexture());
	addObject(optionsButton, optionsButton->getGraphicsComponent()->getSdlTexture());
	addObject(backButton, backButton->getGraphicsComponent()->getSdlTexture());
	addObject(exitButton, exitButton->getGraphicsComponent()->getSdlTexture());

	// Add the scene map to the render map in the Graphics Service
	ServiceLocator::getGraphics().addToRenderMap(_sceneMap);


}