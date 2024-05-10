#include "InEscMenuState.h"
#include "InactiveMenuState.h"
#include "InExitConfirmState.h"
#include "InResoMenuState.h"
#include "ButtonInputComponent.h"
InEscMenuState::InEscMenuState()
{
	
}

void InEscMenuState::enter(SceneEscMenu* menuScene)
{
	if (menuScene->getPreviousState() != nullptr)
	{
		menuScene->getPreviousState()->destroyMenu(menuScene);
	}
	buildMenu(menuScene);
	menuScene->subscribeToEventManager(EventManager::getEventManagerInstance());
	std::cout << "In Escape Menu state entered!\n";	
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
	std::cout << "In Escape Menu state exited!\n";
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
	
	// Set the Z-values
	menuScene->_escMenuBg->setZ(100);
	menuScene->_optionsButton->setZ(101);
	menuScene->_backButton->setZ(102);
	menuScene->_exitButton->setZ(103);

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
	ServiceLocator::getGraphics().addToRenderMap(menuScene->getObjectMap());
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
	// Create vector of Z-values in the current menu objects
	std::vector<int> zValues;
	
	// Add Z-values to the z vector for removal from the render map.
	if (menuScene->_escMenuBg != nullptr)
	{
		zValues.push_back(menuScene->_escMenuBg->getZ());
		menuScene->removeObject(menuScene->_escMenuBg);
		menuScene->_escMenuBg->~Decoration();
	}
	if (menuScene->_optionsButton != nullptr)
	{
		zValues.push_back(menuScene->_optionsButton->getZ());
		menuScene->removeObject(menuScene->_optionsButton);
		menuScene->_optionsButton->~Button();
	}
	if (menuScene->_backButton != nullptr)
	{
		zValues.push_back(menuScene->_backButton->getZ());
		menuScene->removeObject(menuScene->_backButton);
		menuScene->_backButton->~Button();
	}
	if (menuScene->_exitButton != nullptr)
	{
		zValues.push_back(menuScene->_exitButton->getZ());
		menuScene->removeObject(menuScene->_exitButton);
		menuScene->_exitButton->~Button();
	}

	// Remove the objects from the render map and scene using the Z values as the key
	ServiceLocator::getGraphics().removeFromRenderMap(zValues);
	zValues.clear();

}

