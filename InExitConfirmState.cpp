#include "InExitConfirmState.h"
#include "InEscMenuState.h"
#include "ButtonInputComponent.h"
#include "easylogging++.h"


void InExitConfirmState::enter(SceneEscMenu* menuScene)
{
	if (menuScene->getPreviousState() != nullptr)
	{
		menuScene->getPreviousState()->destroyMenu(menuScene);
	}

	buildMenu(menuScene);
	menuScene->subscribeToEventManager(EventManager::getEventManagerInstance());	

	LOG(INFO) << "In Exit Confirmation state entered!\n";
}

void InExitConfirmState::changeState(SceneEscMenu* menuScene, std::string eventString)
{
	
	if (eventString == "Esc" || eventString == "No")
	{
		menuScene->setMenuState(InEscMenuState::getInstance());
	}
	if (eventString == "Yes")
	{		 
		SDL_Event e;
		e.type = SDL_QUIT;
		SDL_PushEvent(&e);
	}


	// If Yes button is pressed:
	// exit game
}

void InExitConfirmState::exit(SceneEscMenu* menuScene)
{
	menuScene->unsubscribeToEventManager(EventManager::getEventManagerInstance());
	LOG(INFO) << "In Exit Confirmation state exited!\n";
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
	menuScene->_exitConfirmMenuBg->setZ(-1);
	
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
	menuScene->addObject(menuScene->_exitConfirmMenuBg, menuScene->_exitConfirmMenuBg->getGraphicsComponent()->getCurrentTexture());
	menuScene->addObject(menuScene->_yes, menuScene->_yes->getGraphicsComponent()->getCurrentTexture());
	menuScene->addObject(menuScene->_no, menuScene->_no->getGraphicsComponent()->getCurrentTexture());

	// Add to render queue
	ServiceLocator::getGraphics().addToRenderMap(4, menuScene->getObjectMap());

}

void InExitConfirmState::destroyMenu(SceneEscMenu* menuScene)
{
	// Remove the objects from the render map
	ServiceLocator::getGraphics().removeFromRenderMap(menuScene->getObjectMap());

	if (menuScene->_exitConfirmMenuBg != nullptr)
	{
		menuScene->removeObject(menuScene->_exitConfirmMenuBg, menuScene->_exitConfirmMenuBg->getGraphicsComponent()->getCurrentTexture());
		menuScene->_exitConfirmMenuBg->~Decoration();
	}
	if (menuScene->_yes != nullptr)
	{
		menuScene->removeObject(menuScene->_yes, menuScene->_yes->getGraphicsComponent()->getCurrentTexture());
		menuScene->_yes->~Button();
	}
	if (menuScene->_no != nullptr)
	{
		menuScene->removeObject(menuScene->_no, menuScene->_no->getGraphicsComponent()->getCurrentTexture());
		menuScene->_no->~Button();
	}
	
	// Clear the menu vector if it is not empty
	if (!menuScene->getObjectMap().empty())
	{
		menuScene->getObjectMap().clear();
	}
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
	manager.Subscribe(SDL_MOUSEBUTTONUP, [this, menuScene](SDL_Event const& event) {
		if (menuScene->getCurrentState() == this)
		{
			menuScene->_yes->getInputComponent()->handleInput(event, *menuScene->_yes, this, menuScene);
			menuScene->_no->getInputComponent()->handleInput(event, *menuScene->_no, this, menuScene);
		}
		});

	// Listen for mouse clicks

}

void InExitConfirmState::unsubscribeToEventManager(EventManager& manager, SceneEscMenu* menuScene)
{
	manager.Unsubscribe(SDL_KEYUP);
	manager.Unsubscribe(SDL_MOUSEBUTTONUP);
}