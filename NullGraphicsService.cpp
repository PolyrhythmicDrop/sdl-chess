#include "NullGraphicsService.h"

Window* NullGraphicsService::getWindow()
{
	return NULL;
}

Renderer* NullGraphicsService::getRenderer()
{
	return NULL;
}

void NullGraphicsService::addToQueue(std::vector<GameObject*>)
{

}

void NullGraphicsService::removeFromQueue()
{

}

void NullGraphicsService::render()
{

}