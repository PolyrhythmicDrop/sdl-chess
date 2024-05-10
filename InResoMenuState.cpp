#include "InResoMenuState.h"
#include "InactiveMenuState.h"
#include "InEscMenuState.h"
#include "ButtonInputComponent.h"

void InResoMenuState::enter(SceneEscMenu* menuScene)
{
	if (menuScene->getPreviousState() != nullptr)
	{
		//menuScene->getPreviousState()->unsubscribeToEventManager(EventManager::getEventManagerInstance(), menuScene);
		menuScene->getPreviousState()->destroyMenu(menuScene);
	}

	buildMenu(menuScene);
	subscribeToEventManager(EventManager::getEventManagerInstance(), menuScene);
	
	std::cout << "In Resolution Menu state entered!\n";
}

void InResoMenuState::changeState(SceneEscMenu* menuScene, std::string eventString)
{
	if (eventString == "Esc")
	{
		menuScene->setMenuState(InactiveMenuState::getInstance());
	}
	if (eventString == "Back")
	{
		menuScene->setMenuState(InEscMenuState::getInstance());
	}
	if (eventString == "1024")
	{
		// Doesn't quite work. Resizes the window, but doesn't adjust button positions or behavior. Consider re-entering the state after this is done?
		ServiceLocator::getGraphics().getWindow()->ResizeWindow(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), 1024, 768);
		menuScene->setMenuState(InResoMenuState::getInstance());
	}
	if (eventString == "1920")
	{
		ServiceLocator::getGraphics().getWindow()->ResizeWindow(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), 1920, 1080);
		menuScene->setMenuState(InResoMenuState::getInstance());
	}
}

void InResoMenuState::exit(SceneEscMenu* menuScene)
{
	menuScene->unsubscribeToEventManager(EventManager::getEventManagerInstance());
	std::cout << "In Resolution Menu state exited!\n";
}

IMenuState& InResoMenuState::getInstance()
{
	static InResoMenuState inReso;
	return inReso;
}

void InResoMenuState::buildMenu(SceneEscMenu* menuScene)
{
	// Instantiate the buttons and decorations
	menuScene->_resoMenuBg = new Decoration(Decoration::RESO_MENU_BG);
	menuScene->_1024 = new Button(Button::TENTWENTYFOUR);
	menuScene->_1920 = new Button(Button::NINETEENTWENTY);
	menuScene->_backButton = new Button(Button::BACK);

	// Set the Z-values
	menuScene->_resoMenuBg->setZ(100);
	menuScene->_1024->setZ(101);
	menuScene->_1920->setZ(102);
	menuScene->_backButton->setZ(103);

	// Get window variables
	int windowW;
	int windowH;
	ServiceLocator::getGraphics().getWindow()->getWindowSize(&windowW, &windowH);

	// Position the objects
	menuScene->_resoMenuBg->setPosition(
		// X Position
		(windowW / 2) - (menuScene->_resoMenuBg->getDimensions()->w / 2),
		// Y Position
		(windowH / 2) - (menuScene->_resoMenuBg->getDimensions()->h / 2)
	);
	menuScene->_1024->setPosition(
		// X position
		(windowW / 2) - (menuScene->_1024->getWidth() / 2),
		// Y position
		menuScene->_resoMenuBg->getDimensions()->y + (menuScene->_resoMenuBg->getDimensions()->h / 4)
	);
	menuScene->_1920->setPosition(
		// X position
		(windowW / 2) - (menuScene->_1920->getWidth() / 2),
		// Y position
		menuScene->_resoMenuBg->getDimensions()->y + ((menuScene->_resoMenuBg->getDimensions()->h / 2) - (menuScene->_1920->getDimensions()->h / 4))
	);
	menuScene->_backButton->setPosition(
		// X position
		(windowW / 2) - (menuScene->_1920->getWidth() / 2),
		// Y position
		menuScene->_resoMenuBg->getDimensions()->y + (menuScene->_backButton->getDimensions()->h * 4)
	);

	// Add to scene map
	menuScene->addObject(menuScene->_resoMenuBg, menuScene->_resoMenuBg->getGraphicsComponent()->getSdlTexture());
	menuScene->addObject(menuScene->_1024, menuScene->_1024->getGraphicsComponent()->getSdlTexture());
	menuScene->addObject(menuScene->_1920, menuScene->_1920->getGraphicsComponent()->getSdlTexture());
	menuScene->addObject(menuScene->_backButton, menuScene->_backButton->getGraphicsComponent()->getSdlTexture());

	// Add to render queue
	ServiceLocator::getGraphics().addToRenderMap(menuScene->getObjectMap());
}

void InResoMenuState::destroyMenu(SceneEscMenu* menuScene)
{
	// Create vector of Z-values in the current menu objects
	std::vector<int> zValues;

	// Add Z-values to the z vector for removal from the render map.
	if (menuScene->_resoMenuBg != nullptr)
	{
		zValues.push_back(menuScene->_resoMenuBg->getZ());
		menuScene->removeObject(menuScene->_resoMenuBg);
		menuScene->_resoMenuBg->~Decoration();
	}
	if (menuScene->_1024 != nullptr)
	{
		zValues.push_back(menuScene->_1024->getZ());
		menuScene->removeObject(menuScene->_1024);
		menuScene->_1024->~Button();
	}
	if (menuScene->_1920 != nullptr)
	{
		zValues.push_back(menuScene->_1920->getZ());
		menuScene->removeObject(menuScene->_1920);
		menuScene->_1920->~Button();
	}
	if (menuScene->_backButton != nullptr)
	{
		zValues.push_back(menuScene->_backButton->getZ());
		menuScene->removeObject(menuScene->_backButton);
		menuScene->_backButton->~Button();
	}

	// Remove the objects from the render map and scene using the Z values as the key
	ServiceLocator::getGraphics().removeFromRenderMap(zValues);
	zValues.clear();
}

void InResoMenuState::subscribeToEventManager(EventManager& manager, SceneEscMenu* menuScene)
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
			menuScene->_1024->getInputComponent()->handleInput(event, *menuScene->_1024, this, menuScene);
			menuScene->_1920->getInputComponent()->handleInput(event, *menuScene->_1920, this, menuScene);
			menuScene->_backButton->getInputComponent()->handleInput(event, *menuScene->_backButton, this, menuScene);
		}
		});
	// Subscribe to window resize events, redraw the menu and positions when this occurs.
	manager.Subscribe(SDL_WINDOWEVENT, [this, menuScene](SDL_Event const& event) {
		if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED || event.window.event == SDL_WINDOWEVENT_RESIZED)
		{	
			SDL_RenderSetLogicalSize(ServiceLocator::getGraphics().getRenderer()->GetRenderer(), event.window.data1, event.window.data2);
			SDL_RenderClear(ServiceLocator::getGraphics().getRenderer()->GetRenderer());
		}		
		});
	
}

void InResoMenuState::unsubscribeToEventManager(EventManager& manager, SceneEscMenu* menuScene)
{
	manager.Unsubscribe(SDL_MOUSEBUTTONUP);
	manager.Unsubscribe(SDL_KEYUP);
	manager.Unsubscribe(SDL_WINDOWEVENT);
}