#include "GraphicsService.h"

GraphicsService::GraphicsService(Window* window) :	

	_window(window), _renderer(new Renderer(window))
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

void GraphicsService::addToRenderMap(std::map<GameObject*, SDL_Texture*> map)
{
	_renderMap.insert(map.begin(), map.end());

	// Debug to make sure objects are being added to the map
	std::map<GameObject*, SDL_Texture*>::iterator itr;
	for (itr = _renderMap.begin(); itr != _renderMap.end(); ++itr)
	{
		std::cout << "Object name " << itr->first->getName() << " has been inserted into the render map!\n";
	}

}

void GraphicsService::removeFromQueue()
{

}

void GraphicsService::render()
{
	// iterator for the map
	std::map<GameObject*, SDL_Texture*>::iterator itr;
	// Set renderer variable
	SDL_Renderer* renderer = _renderer->GetRenderer();
	// Sort the render map by Z value


	// Set the background color and clear the renderer
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
	SDL_RenderClear(renderer);
	for (itr = _renderMap.begin(); itr != _renderMap.end(); ++itr)
	{
		SDL_RenderCopy(renderer, itr->second, NULL, itr->first->getDimensions());
	}
	
	SDL_RenderPresent(renderer);
}


