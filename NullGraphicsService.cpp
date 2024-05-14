#include "NullGraphicsService.h"

Window* NullGraphicsService::getWindow()
{
	return NULL;
}

Renderer* NullGraphicsService::getRenderer()
{
	return NULL;
}

void NullGraphicsService::addToRenderMap(std::map<Layer, std::vector<std::pair<GameObject*, SDL_Texture*>>> map)
{

}

void NullGraphicsService::removeFromRenderMap(std::vector<std::pair<GameObject*, SDL_Texture*>> objects)
{

}

void NullGraphicsService::render()
{

}