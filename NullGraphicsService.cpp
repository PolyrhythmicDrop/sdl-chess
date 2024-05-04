#include "NullGraphicsService.h"

Window* NullGraphicsService::getWindow()
{
	return NULL;
}

Renderer* NullGraphicsService::getRenderer()
{
	return NULL;
}

void NullGraphicsService::addToRenderMap(std::map<GameObject*, SDL_Texture*> map)
{

}

void NullGraphicsService::removeFromQueue()
{

}

void NullGraphicsService::render()
{

}