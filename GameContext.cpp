#include "GameContext.h"

GameContext::GameContext(Window* window, Renderer* renderer) :
	_window{ window }, _renderer{ renderer }
{
	_sdlRenderer = renderer->GetRenderer();
	_sdlWindow = window->getWindow();
	std::cout << "Game context initialized!\n"; 
}

GameContext::~GameContext() { std::cout << "Game context destructed!\n"; };

SDL_Renderer* GameContext::getSdlRenderer()
{
	return this->_sdlRenderer;
}

SDL_Window* GameContext::getSdlWindow()
{
	return this->_sdlWindow;
}
