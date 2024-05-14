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

bool GraphicsService::compareZ(std::pair<GameObject*, SDL_Texture*> a, std::pair<GameObject*, SDL_Texture*> b)
{
	return a.first->getZ() < b.first->getZ();
}

void GraphicsService::addToRenderMap(std::map<Layer, std::vector<std::pair<GameObject*, SDL_Texture*>>> map)
{
	_renderMap.insert(map.begin(), map.end());
	

	// Sort the render map by Z-value
	std::map<Layer, std::vector<std::pair<GameObject*, SDL_Texture*>>>::iterator mItr;
	std::vector<std::pair<GameObject*, SDL_Texture*>>::iterator vItr;
	
	for (mItr = _renderMap.begin(); mItr != _renderMap.end(); ++mItr)
	{
		std::sort(mItr->second.begin(), mItr->second.end(),
			// Lamba defining the comparator
			[](std::pair<GameObject*, SDL_Texture*> a, std::pair<GameObject*, SDL_Texture*> b)
			{ return a.first->getZ() < b.first->getZ(); });
	}
		

	// Debug to make sure objects are being added to the map
	for (const auto &m : _renderMap )
	{
		for (const auto &v : m.second )
		{
			LOG(INFO) << "Object name " << v.first->getName() << " has been inserted into the render map!";
		}
	}

}

void GraphicsService::removeFromRenderMap(std::vector<std::pair<GameObject*, SDL_Texture*>> objects)
{
	std::map<Layer, std::vector<std::pair<GameObject*, SDL_Texture*>>>::iterator itr;

	for (itr = _renderMap.begin(); itr != _renderMap.end(); ++itr)
	{
		itr->second.erase(objects.begin(), objects.end());
	}

}

void GraphicsService::render()
{
	// Set renderer variable
	SDL_Renderer* renderer = _renderer->GetRenderer();

	SDL_SetRenderTarget(renderer, NULL);
	// Set the background color and clear the renderer
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
	SDL_RenderClear(renderer);

	// Render Layer 0
	std::vector<std::pair<GameObject*, SDL_Texture*>>::iterator vItr;
	vItr = _renderMap[GraphicsService::BG].begin();
	for (vItr; vItr != _renderMap[GraphicsService::BG].end(); vItr++)
	{
		SDL_RenderCopy(renderer, vItr->second, NULL, vItr->first->getDimensions());
	}

	// Render Layer 1
	vItr = _renderMap[GraphicsService::BOARD].begin();
	for (vItr; vItr != _renderMap[GraphicsService::BOARD].end(); vItr++)
	{
		SDL_RenderCopy(renderer, vItr->second, NULL, vItr->first->getDimensions());
	}

	// Render Layer 2
	vItr = _renderMap[GraphicsService::PIECES].begin();
	for (vItr; vItr != _renderMap[GraphicsService::PIECES].end(); vItr++)
	{
		SDL_RenderCopy(renderer, vItr->second, NULL, vItr->first->getDimensions());
	}

	// Render Layer 3
	vItr = _renderMap[GraphicsService::UI].begin();
	for (vItr; vItr != _renderMap[GraphicsService::BG].end(); vItr++)
	{
		SDL_RenderCopy(renderer, vItr->second, NULL, vItr->first->getDimensions());
	}

	// Render Layer 4
	vItr = _renderMap[GraphicsService::MENU].begin();
	for (vItr; vItr != _renderMap[GraphicsService::BG].end(); vItr++)
	{
		SDL_RenderCopy(renderer, vItr->second, NULL, vItr->first->getDimensions());
	}

	SDL_RenderPresent(renderer);

	//std::map<int, std::pair<GameObject*, SDL_Texture*>>::iterator it = _renderMap.begin();
	//for (it; it != _renderMap.end(); it++)
	//{
	//	SDL_RenderCopy(renderer, it->second.second, NULL, it->second.first->getDimensions());
	//}

}


