#include "GraphicsService.h"
#include "easylogging++.h"

GraphicsService::GraphicsService(Window* window) :	

	_window(window), _renderer(new Renderer(window))
{
	// Asserts that there are no existing instances of the Graphics Service
	assert(!_instantiated);
	_instantiated = true;
	LOG(INFO) << "Graphics Service initialized!\n";
}

GraphicsService::~GraphicsService()
{
	_instantiated = false;
	LOG(INFO) << "Graphics Service destructed!\n";
}

Window* GraphicsService::getWindow()
{
	return _window;
}

Renderer* GraphicsService::getRenderer()
{
	return _renderer;
}

void GraphicsService::addToRenderMap(std::map<int, std::pair<GameObject*, SDL_Texture*>> map)
{
	_renderMap.insert(map.begin(), map.end());

	// Debug to make sure objects are being added to the map
	std::map<int, std::pair<GameObject*, SDL_Texture*>>::iterator itr;
	for (itr = _renderMap.begin(); itr != _renderMap.end(); ++itr)
	{
		LOG(INFO) << "Object name " << itr->second.first->getName() << " has been inserted into the render map!\n";
	}

}

void GraphicsService::removeFromRenderMap(std::vector<int> zValues)
{
	for (int z : zValues)
	{
		_renderMap.erase(z);
	}
}

void GraphicsService::render()
{
	// Set renderer variable
	SDL_Renderer* renderer = _renderer->GetRenderer();

	// Set the background color and clear the renderer
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
	SDL_RenderClear(renderer);

	std::map<int, std::pair<GameObject*, SDL_Texture*>>::iterator it = _renderMap.begin();
	for (it; it != _renderMap.end(); it++)
	{
		SDL_RenderCopy(renderer, it->second.second, NULL, it->second.first->getDimensions());
	}
	for (auto& square : _squareDrawV)
	{
		if (square->_drawOverlay = true)
		{
			
		}
	}
	
	SDL_RenderPresent(renderer);
}


