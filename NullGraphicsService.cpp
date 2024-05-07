#include "NullGraphicsService.h"

Window* NullGraphicsService::getWindow()
{
	return NULL;
}

Renderer* NullGraphicsService::getRenderer()
{
	return NULL;
}

void NullGraphicsService::addToRenderMap(std::map<int, std::pair<GameObject*, SDL_Texture*>> map)
{

}

void NullGraphicsService::removeFromRenderMap(std::vector<int> zValues)
{

}

void NullGraphicsService::render()
{

}