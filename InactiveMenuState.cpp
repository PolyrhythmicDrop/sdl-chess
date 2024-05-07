#include "InactiveMenuState.h"
#include "InEscMenuState.h"

void InactiveMenuState::enter(SceneEscMenu* menuScene)
{
	subscribeToEventManager(EventManager::getEventManagerInstance(), menuScene);
	std::cout << "Inactive menu state entered!";
}

void InactiveMenuState::changeState(SceneEscMenu* menuScene, std::string eventString)
{
	if (eventString == "Esc")
	{
		menuScene->setMenuState(InEscMenuState::getInstance());
	}
	else
	{
		std::cout << "Could not change state! Please supply an appropriate event string.\n";
	}
}

void InactiveMenuState::exit(SceneEscMenu* menuScene)
{
	std::cout << "Inactive menu state exited!";
}

IMenuState& InactiveMenuState::getInstance()
{
	static InactiveMenuState inactiveState;
	return inactiveState;
}

void InactiveMenuState::buildMenu(SceneEscMenu* menuScene)
{

}

void InactiveMenuState::subscribeToEventManager(EventManager& manager, SceneEscMenu* menuScene)
{
	manager.Subscribe(SDL_KEYUP, [menuScene, this](SDL_Event const& event) {
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			changeState(menuScene, "Esc");
		}
		});
}