#include "SceneEscMenu.h"
#include "InactiveMenuState.h"
#include "InEscMenuState.h"

SceneEscMenu::SceneEscMenu()
{
	_currentState = &InactiveMenuState::getInstance();
}

SceneEscMenu::~SceneEscMenu()
{

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

void SceneEscMenu::buildScene()
{
	


}