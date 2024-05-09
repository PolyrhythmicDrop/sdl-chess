#include "InExitConfirmState.h"
#include "InactiveMenuState.h"

void InExitConfirmState::enter(SceneEscMenu* menuScene)
{
	if (menuScene->getPreviousState() != nullptr)
	{
		menuScene->getPreviousState()->destroyMenu(menuScene);
	}

	buildMenu(menuScene);
	menuScene->subscribeToEventManager(EventManager::getEventManagerInstance());	

	std::cout << "In Exit Confirmation state entered!\n";
}

void InExitConfirmState::changeState(SceneEscMenu* menuScene, std::string eventString)
{
	
	if (eventString == "Esc" || eventString == "No")
	{
		menuScene->setMenuState(InactiveMenuState::getInstance());
	}

	// If No button is pressed:
	// menuScene->setMenuState(InEscMenuState::getInstance());

	// If Yes button is pressed:
	// exit game
}

void InExitConfirmState::exit(SceneEscMenu* menuScene)
{
	menuScene->unsubscribeToEventManager(EventManager::getEventManagerInstance());
	std::cout << "In Exit Confirmation state exited!\n";
}

IMenuState& InExitConfirmState::getInstance()
{
	static InExitConfirmState inExitConfirm;
	return inExitConfirm;
}

void InExitConfirmState::buildMenu(SceneEscMenu* menuScene)
{
	// Instantiate the buttons and backgrounds
	menuScene->_exitConfirmMenuBg = new Decoration(Decoration::EXIT_CONFIRM_BG);
	menuScene->_yes = new Button(Button::YES);
	menuScene->_no = new Button(Button::NO);

	// Set the Z-values
	menuScene->_exitConfirmMenuBg->setZ(100);
	menuScene->_yes->setZ(101);
	menuScene->_no->setZ(102);

	// Get window variables
	int windowW;
	int windowH;
	ServiceLocator::getGraphics().getWindow()->getWindowSize(&windowW, &windowH);

	// Set positions
	menuScene->_exitConfirmMenuBg->setPosition(
		// X position
		((windowW / 2) - (menuScene->_exitConfirmMenuBg->getDimensions()->w / 2)),
		// Y position
		((windowH / 2) - (menuScene->_exitConfirmMenuBg->getDimensions()->h / 2))
	);
	menuScene->_yes->setPosition(
		// X position
		((menuScene->_exitConfirmMenuBg->getDimensions()->x) + (menuScene->_yes->getDimensions()->w / 4)),
		// Y position
		((menuScene->_exitConfirmMenuBg->getDimensions()->y + menuScene->_exitConfirmMenuBg->getDimensions()->h) - ((menuScene->_yes->getDimensions()->h) + (menuScene->_yes->getDimensions()->h / 2)))
	);
	menuScene->_no->setPosition(
		// X position
		(menuScene->_exitConfirmMenuBg->getDimensions()->x + menuScene->_exitConfirmMenuBg->getDimensions()->w) - (menuScene->_no->getDimensions()->w + (menuScene->_no->getDimensions()->w / 4)),
		// Y position
		(menuScene->_yes->getDimensions()->y )
	);
	
	// Add to scene map
	menuScene->addObject(menuScene->_exitConfirmMenuBg, menuScene->_exitConfirmMenuBg->getGraphicsComponent()->getSdlTexture());
	menuScene->addObject(menuScene->_yes, menuScene->_yes->getGraphicsComponent()->getSdlTexture());
	menuScene->addObject(menuScene->_no, menuScene->_no->getGraphicsComponent()->getSdlTexture());

	// Add to render queue
	ServiceLocator::getGraphics().addToRenderMap(menuScene->getObjectMap());

}

void InExitConfirmState::destroyMenu(SceneEscMenu* menuScene)
{

}

void InExitConfirmState::subscribeToEventManager(EventManager& manager, SceneEscMenu* menuScene)
{
	// Subscribe to listen for the Escape key to be released, then change the state.
	manager.Subscribe(SDL_KEYUP, [this, menuScene](SDL_Event const& event) {
		if (event.key.keysym.sym == SDLK_ESCAPE && menuScene->getCurrentState() == this)
		{
			changeState(menuScene, "Esc");
		}
		});
	manager.Subscribe(SDL_MOUSEBUTTONUP, [this, menuScene](SDL_Event const& event) {});

	// Listen for mouse clicks

}

void InExitConfirmState::unsubscribeToEventManager(EventManager& manager, SceneEscMenu* menuScene)
{
	manager.Unsubscribe(SDL_KEYUP);
	manager.Unsubscribe(SDL_MOUSEBUTTONUP);
}