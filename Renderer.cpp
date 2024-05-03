#include "Renderer.h"

Renderer::Renderer(Window* window) 
{
	int w, h;
	SDL_Renderer* renderer = SDL_CreateRenderer(window->getWindow(), -1, SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	window->getWindowSize(&w, &h);
	SDL_RenderSetLogicalSize(renderer, w, h);
	_sdlRenderer = renderer;
	std::cout << "Renderer initialized!\n";
}

Renderer::~Renderer()
{
	std::cout << "Renderer destructed!\n";
}

SDL_Renderer* Renderer::GetRenderer()
{
	return _sdlRenderer;
}