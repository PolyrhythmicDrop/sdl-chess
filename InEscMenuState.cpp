#include "InEscMenuState.h"
#include "InactiveMenuState.h"
#include "PlayerInputComponent.h"

void InEscMenuState::enter(SceneEscMenu* menuScene)
{
	subscribeToEventManager(EventManager::getEventManagerInstance(), menuScene);
	std::cout << "In Escape Menu state entered!\n";
	buildMenu(menuScene);
}

void InEscMenuState::changeState(SceneEscMenu* menuScene, std::string eventString)
{
	menuScene->setMenuState(InactiveMenuState::getInstance());
}

void InEscMenuState::exit(SceneEscMenu* menuScene)
{
	unsubscribeToEventManager(EventManager::getEventManagerInstance(), menuScene);
	destroyMenu(menuScene);
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
	Decoration* escMenuBg = new Decoration(Decoration::ESC_MENU_BG);
	Button* optionsButton = new Button(Button::OPTIONS, new PlayerInputComponent());
	Button* backButton = new Button(Button::BACK, new PlayerInputComponent());
	Button* exitButton = new Button(Button::EXIT_GAME, new PlayerInputComponent());

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

	menuScene->_currentMenuObjects.push_back(escMenuBg);
	menuScene->_currentMenuObjects.push_back(optionsButton);
	menuScene->_currentMenuObjects.push_back(backButton);
	menuScene->_currentMenuObjects.push_back(exitButton);


	// Add the scene map to the render map in the Graphics Service
	ServiceLocator::getGraphics().addToRenderMap(menuScene->getObjectMap());
}

void InEscMenuState::destroyMenu(SceneEscMenu* menuScene)
{
	// Create vector of Z-values in the current menu objects
	std::vector<int> zValues;
	for (GameObject* obj : menuScene->_currentMenuObjects)
	{
		zValues.push_back(obj->getZ());
	}

	// Remove the objects from the render map using the Z values as the key
	ServiceLocator::getGraphics().removeFromRenderMap(zValues);
	
	// Destroy the game objects
	for (GameObject* obj : menuScene->_currentMenuObjects)
	{
		obj->~GameObject();
	}

	// Remove the vector of game current menu objects
	menuScene->_currentMenuObjects.clear();
	zValues.clear();
	
}

void InEscMenuState::subscribeToEventManager(EventManager& manager, SceneEscMenu* menuScene)
{
	// Subscribe to listen for the Escape key to be released, then change the state.
	manager.Subscribe(SDL_KEYUP, [this, menuScene](SDL_Event const& event) {
		if (event.key.keysym.sym == SDLK_ESCAPE && menuScene->getCurrentState() == this)
		{
			changeState(menuScene, "");
		}
		});
}

void InEscMenuState::unsubscribeToEventManager(EventManager& manager, SceneEscMenu* menuScene)
{
	manager.Unsubscribe(SDL_KEYUP);
}