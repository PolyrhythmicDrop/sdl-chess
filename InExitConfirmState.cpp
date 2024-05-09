#include "InExitConfirmState.h"

void InExitConfirmState::enter(SceneEscMenu* menuScene)
{
	std::cout << "In Exit Confirmation state entered!\n";

	menuScene->subscribeToEventManager(EventManager::getEventManagerInstance());
}

void InExitConfirmState::changeState(SceneEscMenu* menuScene, std::string eventString)
{
	// If Esc key is pressed:
	// menuScene->setMenuState(InEscMenuState::getInstance());

	// If No button is pressed:
	// menuScene->setMenuState(InEscMenuState::getInstance());

	// If Yes button is pressed:
	// exit game
}

void InExitConfirmState::exit(SceneEscMenu* menuScene)
{
	std::cout << "In Exit Confirmation state exited!\n";
}

IMenuState& InExitConfirmState::getInstance()
{
	static InExitConfirmState inExitConfirm;
	return inExitConfirm;
}

void InExitConfirmState::buildMenu(SceneEscMenu* menuScene)
{

}

void InExitConfirmState::destroyMenu(SceneEscMenu* menuScene)
{

}

void InExitConfirmState::subscribeToEventManager(EventManager& manager, SceneEscMenu* menuScene)
{

}

void InExitConfirmState::unsubscribeToEventManager(EventManager& manager, SceneEscMenu* menuScene)
{
	// manager.Unsubscribe(SDL_KEYUP);
}