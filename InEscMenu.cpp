#include "InEscMenu.h"
#include "InactiveMenuState.h"

void InEscMenu::enter(SceneEscMenu* menuScene)
{
	std::cout << "In Escape Menu state entered!";
}

void InEscMenu::toggleState(SceneEscMenu* menuScene)
{
	menuScene->setState(InactiveMenuState::getInstance());
}

void InEscMenu::exit(SceneEscMenu* menuScene)
{
	std::cout << "In Escape Menu state exited!";
}

IMenuState& InEscMenu::getInstance()
{
	static InEscMenu inEsc;
	return inEsc;
}