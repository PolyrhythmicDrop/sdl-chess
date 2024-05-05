#include "GameContext.h"

GameContext::GameContext() 
{	
	// Asserts that there are no existing instances of the Graphics Service
	assert(!_instantiated);
	_instantiated = true;
	std::cout << "Game context initialized!\n"; 
}

GameContext::~GameContext() { std::cout << "Game context destructed!\n"; };
