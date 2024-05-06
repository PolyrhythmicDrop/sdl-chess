#include "InEscMenuState.h"
#include "InactiveMenuState.h"

void InEscMenuState::enter(SceneEscMenu* menuScene)
{
	std::cout << "In Escape Menu state entered!";
	buildEscMenu(menuScene);
}

void InEscMenuState::changeState(SceneEscMenu* menuScene)
{
	menuScene->setMenuState(InactiveMenuState::getInstance());
}

void InEscMenuState::exit(SceneEscMenu* menuScene)
{
	std::cout << "In Escape Menu state exited!";
}

IMenuState& InEscMenuState::getInstance()
{
	static InEscMenuState inEsc;
	return inEsc;
}

void InEscMenuState::buildEscMenu(SceneEscMenu* menuScene)
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
	escMenuBg->setPosition((windowW / 2) - (escMenuBg->getWidth() / 2), (windowH / 2) - (escMenuBg->getHeight() / 2));

	optionsButton->setPosition((windowW / 2) - (optionsButton->getWidth() / 2), (escMenuBg->getDimensions()->y + (optionsButton->getHeight() / 2)));

	backButton->setPosition((windowW / 2) - (backButton->getWidth() / 2), ((escMenuBg->getDimensions()->y) + (escMenuBg->getHeight() / 2)) - (backButton->getHeight() / 2));

	exitButton->setPosition((windowW / 2) - (exitButton->getWidth() / 2), (escMenuBg->getDimensions()->y + escMenuBg->getHeight() - exitButton->getHeight()) - (exitButton->getHeight() / 2));

	// Add the objects to the scene map
	menuScene->addObject(escMenuBg, escMenuBg->getGraphicsComponent()->getSdlTexture());
	menuScene->addObject(optionsButton, optionsButton->getGraphicsComponent()->getSdlTexture());
	menuScene->addObject(backButton, backButton->getGraphicsComponent()->getSdlTexture());
	menuScene->addObject(exitButton, exitButton->getGraphicsComponent()->getSdlTexture());


	// Add the scene map to the render map in the Graphics Service
	ServiceLocator::getGraphics().addToRenderMap(menuScene->getObjectMap());
}