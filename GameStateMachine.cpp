#include "GameStateMachine.h"
#include "InitGameState.h"
#include "GameScene.h"


GameStateMachine::GameStateMachine(GameManager* gm) :
	_manager(gm)
{
	assert(!_instantiated);
	_instantiated = true;
}

void GameStateMachine::enter(GameManager* gm)
{
	gm->getCurrentState()->enter(this);
}

void GameStateMachine::changeState(GameManager* gm, std::string eventString)
{
	gm->getCurrentState()->changeState(this, eventString);
}

void GameStateMachine::exit(GameManager* gm)
{
	gm->getCurrentState()->exit(this);
}

void GameStateMachine::setGameState(GameManager* gm, IGameState& newState)
{
	if (gm->_currentState != nullptr)
	{
		gm->_previousState = gm->_currentState;
		gm->_currentState->exit(this);
	}
	gm->_currentState = &newState;
	gm->_currentState->enter(this);
}

void GameStateMachine::subscribeToEventManager(EventManager& manager, GameManager* gm)
{
	gm->getCurrentState()->subscribeToEventManager(manager, this);
}

void GameStateMachine::unsubscribeToEventManager(EventManager& manager, GameManager* gm)
{
	gm->getCurrentState()->unsubscribeToEventManager(manager, this);
}