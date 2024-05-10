#include "InactiveMenuState.h"
#include "InEscMenuState.h"

void InactiveMenuState::enter(SceneEscMenu* menuScene)
{
	if (menuScene->getPreviousState() != nullptr)
	{		
		menuScene->getPreviousState()->destroyMenu(menuScene);
	}
	//menuScene->subscribeToEventManager(EventManager::getEventManagerInstance());

	int menuExit = SDL_RegisterEvents(1);
	SDL_Event e;
	e.user.type = menuExit;
	e.user.code = 15 + 5;	
	SDL_PushEvent(&e);

	std::cout << "Inactive menu state entered!\n";
}

void InactiveMenuState::changeState(SceneEscMenu* menuScene, std::string eventString)
{
	menuScene->setMenuState(InEscMenuState::getInstance());
}

void InactiveMenuState::exit(SceneEscMenu* menuScene)
{
	//menuScene->unsubscribeToEventManager(EventManager::getEventManagerInstance());
	std::cout << "Inactive menu state exited!\n";
}

IMenuState& InactiveMenuState::getInstance()
{
	static InactiveMenuState inactiveState;
	return inactiveState;
}

void InactiveMenuState::buildMenu(SceneEscMenu* menuScene)
{

}

void InactiveMenuState::destroyMenu(SceneEscMenu* menuScene)
{

}

void InactiveMenuState::subscribeToEventManager(EventManager& manager, SceneEscMenu* menuScene)
{
	// Moved the Esc key trigger to the Game State Machine to trigger the creation of the menu
	/*
	manager.Subscribe(SDL_KEYUP, [this, menuScene](SDL_Event const& event) {
		if (event.key.keysym.sym == SDLK_ESCAPE && menuScene->getCurrentState() == this)
		{
			changeState(menuScene, "");
		}
		});
	*/
}

void InactiveMenuState::unsubscribeToEventManager(EventManager& manager, SceneEscMenu* menuScene)
{
	// Do not need to unsubscribe now that we never subscribe
	// manager.Unsubscribe(SDL_KEYUP);
}