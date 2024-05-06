#include "InactiveMenuState.h"
#include "InEscMenu.h"

void InactiveMenuState::enter(SceneEscMenu* menuScene)
{
	std::cout << "Inactive menu state entered!";
}

void InactiveMenuState::changeState(SceneEscMenu* menuScene)
{
	menuScene->setMenuState(InEscMenu::getInstance());
}

void InactiveMenuState::exit(SceneEscMenu* menuScene)
{
	std::cout << "Inactive menu state exited!";
}

IMenuState& InactiveMenuState::getInstance()
{
	static InactiveMenuState singleton;
	return singleton;
}