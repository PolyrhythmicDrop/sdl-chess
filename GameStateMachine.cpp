#include "GameStateMachine.h"
#include "InitGameState.h"
#include "GameScene.h"


GameStateMachine::GameStateMachine(GameScene* scene) :
	_gameScene(scene)
{
	assert(!_instantiated);
	_instantiated = true;
}

void GameStateMachine::enter(GameScene* scene)
{
	scene->getCurrentState()->enter(this);
}

void GameStateMachine::changeState(GameScene* scene)
{
	scene->getCurrentState()->changeState(this);
}

void GameStateMachine::exit(GameScene* scene)
{
	scene->getCurrentState()->exit(this);
}

void GameStateMachine::setGameState(GameScene* scene, IGameState& newState)
{
	if (scene->_currentState != nullptr)
	{
		scene->_previousState = scene->_currentState;
		scene->_currentState->exit(this);
	}
	scene->_currentState = &newState;
	scene->_currentState->enter(this);
}

void GameStateMachine::subscribeToEventManager(EventManager& manager, GameScene* scene)
{
	scene->getCurrentState()->subscribeToEventManager(manager, this);
}

void GameStateMachine::unsubscribeToEventManager(EventManager& manager, GameScene* scene)
{
	scene->getCurrentState()->unsubscribeToEventManager(manager, this);
}