#include "SceneEscMenu.h"
#include "InactiveMenuState.h"

SceneEscMenu::SceneEscMenu() :
	_escMenuBg(nullptr),
	_optionsButton(nullptr),
	_backButton(nullptr),
	_exitButton(nullptr),
	_previousState(nullptr),
	_resoMenuBg(nullptr),
	_yes(nullptr),
	_no(nullptr)
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
	if (_previousState != _currentState)
	{
		_previousState = _currentState;
	}
	_currentState->exit(this);
	_currentState = &newState;
	_currentState->enter(this);
}

void SceneEscMenu::buildMenu()
{
	_currentState->buildMenu(this);
}