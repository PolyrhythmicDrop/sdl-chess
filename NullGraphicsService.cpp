#include "NullGraphicsService.h"

Window* NullGraphicsService::getWindow()
{
	return nullptr;
}

Renderer* NullGraphicsService::getRenderer()
{
	return nullptr;
}

void NullGraphicsService::addToRenderMap(int layer, std::vector<IDrawable*> objects)
{

}

void NullGraphicsService::removeFromRenderMap(std::vector<IDrawable*> objects)
{

}

std::vector<IDrawable*> NullGraphicsService::findInRenderMap(std::vector<IDrawable*> objects)
{
	return objects;
}

void NullGraphicsService::render()
{

}