#include "GameContext.h"
#include "easylogging++.h"

GameContext::GameContext()
{	
	// Asserts that there are no existing instances of the GameContext
	assert(!_instantiated);
	_instantiated = true;
	_gameObjects.reserve(5);
	LOG(INFO) << "Game context initialized!\n"; 
}

GameContext::~GameContext() { LOG(INFO) << "Game context destructed!\n"; };
