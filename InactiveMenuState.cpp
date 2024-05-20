#include "InactiveMenuState.h"
#include "InEscMenuState.h"
#include "easylogging++.h"

void InactiveMenuState::enter(SceneEscMenu* menuScene)
{
	if (menuScene->getPreviousState() != nullptr)
	{		
		menuScene->getPreviousState()->destroyMenu(menuScene);
	}

	menuScene->active = false;
	menuScene->sendStatus(menuScene->active);
	

	LOG(INFO) << "Inactive menu state entered!\n";
}

void InactiveMenuState::changeState(SceneEscMenu* menuScene, std::string eventString)
{
	menuScene->setMenuState(InEscMenuState::getInstance());
}

void InactiveMenuState::exit(SceneEscMenu* menuScene)
{
	//menuScene->unsubscribeToEventManager(EventManager::getEventManagerInstance());
	LOG(INFO) << "Inactive menu state exited!\n";
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

}

void InactiveMenuState::unsubscribeToEventManager(EventManager& manager, SceneEscMenu* menuScene)
{

}