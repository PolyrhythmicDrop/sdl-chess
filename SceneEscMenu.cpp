#include "SceneEscMenu.h"
#include "InactiveMenuState.h"

SceneEscMenu::SceneEscMenu(InputComponent* input) :
	_input(input)
{
	_currentState = &InactiveMenuState::getInstance();
	setMenuState(InactiveMenuState::getInstance());
}

SceneEscMenu::~SceneEscMenu()
{

}

void SceneEscMenu::subscribeToEventManager(EventManager& manager)
{
	_currentState->subscribeToEventManager(manager, this);
}

void SceneEscMenu::changeState()
{
	_currentState->changeState(this, "Esc");
}

void SceneEscMenu::setMenuState(IMenuState& newState)
{
	_currentState->exit(this);
	_currentState = &newState;
	_currentState->enter(this);
}

InputComponent* SceneEscMenu::getInputComponent()
{
	return _input->getInputComponent();
}

void SceneEscMenu::buildMenu()
{
	_currentState->buildMenu(this);
}