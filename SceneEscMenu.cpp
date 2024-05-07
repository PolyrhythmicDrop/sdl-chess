#include "SceneEscMenu.h"
#include "InactiveMenuState.h"

SceneEscMenu::SceneEscMenu()
{
	_currentState = &InactiveMenuState::getInstance();
	_currentState->enter(this);
}

SceneEscMenu::~SceneEscMenu()
{

}

void SceneEscMenu::subscribeToEventManager(EventManager& manager)
{
	_currentState->subscribeToEventManager(manager, this);
}

void SceneEscMenu::unsubscribeToEventManager(EventManager& manager)
{
	_currentState->unsubscribeToEventManager(manager, this);
}

void SceneEscMenu::changeState()
{
	_currentState->changeState(this);
}

void SceneEscMenu::setMenuState(IMenuState& newState)
{
	_currentState->exit(this);
	_currentState = &newState;
	_currentState->enter(this);
}

void SceneEscMenu::buildMenu()
{
	_currentState->buildMenu(this);
}