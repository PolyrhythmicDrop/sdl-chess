#include "InResoMenuState.h"
#include "InactiveMenuState.h"
#include "InEscMenuState.h"

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
	// If Esc key is pressed:
	// menuScene->setMenuState(InactiveMenuState::getInstance());

	// If Back button is pressed:
	// menuScene->setMenuState(InEscMenuState::getInstance());

	// If 1024x768 button is pressed:
	// resizeWindow(1024, 768);
	// Stay in current state?

	// If 1920x1080 is pressed:
	// resizeWindow(1920, 1080)
	// Stay in current state?
}

void InResoMenuState::exit(SceneEscMenu* menuScene)
{
	std::cout << "In Resolution Menu state exited!\n";
}

IMenuState& InResoMenuState::getInstance()
{
	static InResoMenuState inReso;
	return inReso;
}

void InResoMenuState::buildMenu(SceneEscMenu* menuScene)
{

}

void InResoMenuState::destroyMenu(SceneEscMenu* menuScene)
{

}

void InResoMenuState::subscribeToEventManager(EventManager& manager, SceneEscMenu* menuScene)
{

}

void InResoMenuState::unsubscribeToEventManager(EventManager& manager, SceneEscMenu* menuScene)
{
	// manager.Unsubscribe(SDL_KEYUP);
}