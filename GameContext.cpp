#include "GameContext.h"
#include "Window.h"

GameContext::GameContext(SDL_Window* window, Renderer renderer) :
	_window{ window }, _renderer{ renderer }
{ std::cout << "Game context initialized!"; }

GameContext::~GameContext() { std::cout << "Game context deconstructed"; };
