#include "GraphicsService.h"

GraphicsService::GraphicsService(Window* window) :	
	_window(window),
	_renderer(new Renderer(window))
{
	// Asserts that there are no existing instances of the Graphics Service
	assert(!_instantiated);
	_instantiated = true;
	std::cout << "Graphics Service initialized!\n";
}

GraphicsService::~GraphicsService()
{
	_instantiated = false;
	std::cout << "Graphics Service destructed!\n";
}

Window* GraphicsService::getWindow()
{
	return _window;
}

Renderer* GraphicsService::getRenderer()
{
	return _renderer;
}

void GraphicsService::removeFromQueue()
{

}

void GraphicsService::drawQueue()
{

}


