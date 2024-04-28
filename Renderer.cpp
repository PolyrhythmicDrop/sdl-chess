#include "Renderer.h"

Renderer::Renderer(Window window) 
{
	SDL_Renderer* renderer = SDL_CreateRenderer(window.getWindow(), -1, SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_ACCELERATED);
	SDL_RenderSetLogicalSize(renderer, window.getWindowWidth(), window.getWindowHeight());
	_renderer = renderer;
}

Renderer::~Renderer()
{
	std::cout << "Renderer destructed!";
}

void Renderer::Init(Window window)
{
	
}

SDL_Renderer* Renderer::GetRenderer()
{
	return _renderer;
}