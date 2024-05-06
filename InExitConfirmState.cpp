#include "InExitConfirmState.h"

void InExitConfirmState::enter(SceneEscMenu* menuScene)
{
	std::cout << "In Exit Confirmation state entered!\n";
}

void InExitConfirmState::changeState(SceneEscMenu* menuScene)
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
	std::cout << "In ExitConfirmation state exited!\n";
}

IMenuState& InExitConfirmState::getInstance()
{
	static InExitConfirmState inExitConfirm;
	return inExitConfirm;
}