#include "InEscMenuState.h"
#include "InactiveMenuState.h"

void InEscMenuState::enter(SceneEscMenu* menuScene)
{
	std::cout << "In Escape Menu state entered!";
}

void InEscMenuState::changeState(SceneEscMenu* menuScene)
{
	menuScene->setMenuState(InactiveMenuState::getInstance());
}

void InEscMenuState::exit(SceneEscMenu* menuScene)
{
	std::cout << "In Escape Menu state exited!";
}

IMenuState& InEscMenuState::getInstance()
{
	static InEscMenuState inEsc;
	return inEsc;
}