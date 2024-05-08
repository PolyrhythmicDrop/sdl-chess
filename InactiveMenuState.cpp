#include "InactiveMenuState.h"
#include "InEscMenuState.h"

void InactiveMenuState::enter(SceneEscMenu* menuScene)
{
	if (menuScene->getPreviousState() != nullptr)
	{
		menuScene->getPreviousState()->unsubscribeToEventManager(EventManager::getEventManagerInstance(), menuScene);
		menuScene->getPreviousState()->destroyMenu(menuScene);
	}
	subscribeToEventManager(EventManager::getEventManagerInstance(), menuScene);
	std::cout << "Inactive menu state entered!\n";
}

void InactiveMenuState::changeState(SceneEscMenu* menuScene, std::string eventString)
{
	menuScene->setMenuState(InEscMenuState::getInstance());
}

void InactiveMenuState::exit(SceneEscMenu* menuScene)
{
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
	manager.Subscribe(SDL_KEYUP, [this, menuScene](SDL_Event const& event) {
		if (event.key.keysym.sym == SDLK_ESCAPE && menuScene->getCurrentState() == this)
		{
			changeState(menuScene, "");
		}
		});
}

void InactiveMenuState::unsubscribeToEventManager(EventManager& manager, SceneEscMenu* menuScene)
{
	manager.Unsubscribe(SDL_KEYUP);
}