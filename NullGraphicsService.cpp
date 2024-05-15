#include "NullGraphicsService.h"

Window* NullGraphicsService::getWindow()
{
	return NULL;
}

Renderer* NullGraphicsService::getRenderer()
{
	return NULL;
}

void NullGraphicsService::addToRenderMap(int layer, std::vector<std::pair<GameObject*, SDL_Texture*>> pairs)
{

}

void NullGraphicsService::removeFromRenderMap(std::vector<std::pair<GameObject*, SDL_Texture*>> objects)
{

}

std::vector<std::pair<GameObject*, SDL_Texture*>> NullGraphicsService::findInRenderMap(std::vector<std::pair<GameObject*, SDL_Texture*>> objects)
{
	return std::vector<std::pair<GameObject*, SDL_Texture*>>(NULL);
}

void NullGraphicsService::render()
{

}