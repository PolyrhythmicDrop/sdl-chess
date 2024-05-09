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