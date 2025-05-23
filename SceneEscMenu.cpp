#include "SceneEscMenu.h"
#include "InactiveMenuState.h"

SceneEscMenu::SceneEscMenu() :
	_escMenuBg(nullptr),
	_optionsButton(nullptr),
	_backButton(nullptr),
	_exitButton(nullptr),
	_previousState(nullptr),
	_exitConfirmMenuBg(nullptr),
	_yes(nullptr),
	_no(nullptr),
	_resoMenuBg(nullptr),
	_1024(nullptr),
	_1920(nullptr),
	_currentState(nullptr),
	active(false)
{
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

bool SceneEscMenu::getStatus() const
{
	return this->active;
}

void SceneEscMenu::addListener(bool active, activeCallback callback)
{
	_listenerList[active].push_back(callback);
}

void SceneEscMenu::removeListener(bool active)
{
	_listenerList[active].clear();
}

void SceneEscMenu::sendStatus(bool active)
{
	for (auto& cb : _listenerList[active])
	{
		cb(active);
	}
}

void SceneEscMenu::changeState()
{
	_currentState->changeState(this);
}

void SceneEscMenu::setMenuState(IMenuState& newState)
{
	if (_currentState != nullptr)
	{
		_previousState = _currentState;
		_currentState->exit(this);
	}
	_currentState = &newState;
	_currentState->enter(this);
}

void SceneEscMenu::buildMenu()
{
	_currentState->buildMenu(this);
}