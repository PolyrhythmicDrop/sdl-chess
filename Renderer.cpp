#include "Renderer.h"
#include "easylogging++.h"

Renderer::Renderer(Window* window) 
{
	int w, h;
	SDL_Renderer* renderer = SDL_CreateRenderer(window->getWindow(), -1, SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_ACCELERATED );
	window->getWindowSize(&w, &h);
	SDL_SetHint(SDL_HINT_RENDER_LOGICAL_SIZE_MODE, "0");
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	SDL_SetHint(SDL_HINT_RENDER_LINE_METHOD, "3");
	SDL_RenderSetLogicalSize(renderer, w, h);
	_sdlRenderer = renderer;
	LOG(INFO) << "Renderer initialized!";
}

Renderer::~Renderer()
{
	LOG(INFO) << "Renderer destructed!";
}

SDL_Renderer* Renderer::GetRenderer()
{
	return _sdlRenderer;
}