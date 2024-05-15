#include "InEscMenuState.h"
#include "InactiveMenuState.h"
#include "InExitConfirmState.h"
#include "InResoMenuState.h"
#include "ButtonInputComponent.h"
#include "easylogging++.h"

InEscMenuState::InEscMenuState()
{
	
}

void InEscMenuState::enter(SceneEscMenu* menuScene)
{
	if (menuScene->getPreviousState() != nullptr)
	{
		menuScene->getPreviousState()->destroyMenu(menuScene);
	}
	menuScene->active = true;
	buildMenu(menuScene);
	menuScene->subscribeToEventManager(EventManager::getEventManagerInstance());
	LOG(INFO) << "In Escape Menu state entered!\n";	
}

void InEscMenuState::changeState(SceneEscMenu* menuScene, std::string eventString)
{
	// Deactivate the menu if the Escape key is pressed or the Back button is clicked.
	if (eventString == "Esc" || eventString == "Back")
	{
		menuScene->setMenuState(InactiveMenuState::getInstance());
	}
	// Move to the exit confirmation dialog if the exit button is pressed.
	if (eventString == "ExitGame")
	{
		menuScene->setMenuState(InExitConfirmState::getInstance());
	}
	if (eventString == "Options")
	{
		menuScene->setMenuState(InResoMenuState::getInstance());
	}

}

void InEscMenuState::exit(SceneEscMenu* menuScene)
{
	menuScene->unsubscribeToEventManager(EventManager::getEventManagerInstance());
	LOG(INFO) << "In Escape Menu state exited!\n";
}

IMenuState& InEscMenuState::getInstance()
{
	static InEscMenuState inEsc;
	return inEsc;
}

void InEscMenuState::buildMenu(SceneEscMenu* menuScene)
{
	// Instantiate the buttons and backgrounds	
	menuScene->_escMenuBg = new Decoration(Decoration::ESC_MENU_BG);
	menuScene->_optionsButton = new Button(Button::OPTIONS);
	menuScene->_backButton = new Button(Button::BACK);
	menuScene->_exitButton = new Button(Button::EXITGAME);

	// Get window variables
	int windowW;
	int windowH;
	ServiceLocator::getGraphics().getWindow()->getWindowSize(&windowW, &windowH);

	// Set the positions
	menuScene->_escMenuBg->setPosition(
		// X position
		(windowW / 2) - (menuScene->_escMenuBg->getWidth() / 2),
		// Y position
		(windowH / 2) - (menuScene->_escMenuBg->getHeight() / 2));

	menuScene->_optionsButton->setPosition(
		// X position
		(windowW / 2) - (menuScene->_optionsButton->getWidth() / 2),
		// Y position
		(menuScene->_escMenuBg->getDimensions()->y + (menuScene->_optionsButton->getHeight() / 2)));

	menuScene->_backButton->setPosition((windowW / 2) - (menuScene->_backButton->getWidth() / 2), ((menuScene->_escMenuBg->getDimensions()->y) + (menuScene->_escMenuBg->getHeight() / 2)) - (menuScene->_backButton->getHeight() / 2));

	menuScene->_exitButton->setPosition((windowW / 2) - (menuScene->_exitButton->getWidth() / 2), (menuScene->_escMenuBg->getDimensions()->y + menuScene->_escMenuBg->getHeight() - menuScene->_exitButton->getHeight()) - (menuScene->_exitButton->getHeight() / 2));

	// Add the objects to the scene map
	menuScene->addObject(menuScene->_escMenuBg, menuScene->_escMenuBg->getGraphicsComponent()->getSdlTexture());
	menuScene->addObject(menuScene->_optionsButton, menuScene->_optionsButton->getGraphicsComponent()->getSdlTexture());
	menuScene->addObject(menuScene->_backButton, menuScene->_backButton->getGraphicsComponent()->getSdlTexture());
	menuScene->addObject(menuScene->_exitButton, menuScene->_exitButton->getGraphicsComponent()->getSdlTexture());


	// Add the scene map to the render map in the Graphics Service
	ServiceLocator::getGraphics().addToRenderMap(4, menuScene->getObjectMap());
	
}

void InEscMenuState::subscribeToEventManager(EventManager& manager, SceneEscMenu* menuScene)
{
	// Subscribe to listen for the Escape key to be released, then change the state.
	manager.Subscribe(SDL_KEYUP, [this, menuScene](SDL_Event const& event) {
		if (event.key.keysym.sym == SDLK_ESCAPE && menuScene->getCurrentState() == this)
		{
			changeState(menuScene, "Esc");
		}
		});
	//Subscribe the buttons
	manager.Subscribe(SDL_MOUSEBUTTONUP, [this, menuScene](SDL_Event const& event) {
		if (event.type == SDL_MOUSEBUTTONUP && menuScene->getCurrentState() == this)
		{
			menuScene->_exitButton->getInputComponent()->handleInput(event, *menuScene->_exitButton, this, menuScene);
			menuScene->_optionsButton->getInputComponent()->handleInput(event, *menuScene->_optionsButton, this, menuScene);
			menuScene->_backButton->getInputComponent()->handleInput(event, *menuScene->_backButton, this, menuScene);
		}
		});
}

void InEscMenuState::unsubscribeToEventManager(EventManager& manager, SceneEscMenu* menuScene)
{
	manager.Unsubscribe(SDL_MOUSEBUTTONUP);
	manager.Unsubscribe(SDL_KEYUP);	
}

void InEscMenuState::destroyMenu(SceneEscMenu* menuScene)
{
	// Remove the objects from the render map
	ServiceLocator::getGraphics().removeFromRenderMap(menuScene->getObjectMap());
	
	
	if (menuScene->_escMenuBg != nullptr)
	{
		menuScene->removeObject(menuScene->_escMenuBg, menuScene->_escMenuBg->getGraphicsComponent()->getSdlTexture());
		menuScene->_escMenuBg->~Decoration();
	}
	if (menuScene->_optionsButton != nullptr)
	{
		menuScene->removeObject(menuScene->_optionsButton, menuScene->_optionsButton->getGraphicsComponent()->getSdlTexture());
		menuScene->_optionsButton->~Button();
	}
	if (menuScene->_backButton != nullptr)
	{
		menuScene->removeObject(menuScene->_backButton, menuScene->_backButton->getGraphicsComponent()->getSdlTexture());
		menuScene->_backButton->~Button();
	}
	if (menuScene->_exitButton != nullptr)
	{
		menuScene->removeObject(menuScene->_exitButton, menuScene->_exitButton->getGraphicsComponent()->getSdlTexture());
		menuScene->_exitButton->~Button();
	}

	// Clear the menu vector if it is not empty
	if (!menuScene->getObjectMap().empty())
	{
		menuScene->getObjectMap().clear();
	}

}

