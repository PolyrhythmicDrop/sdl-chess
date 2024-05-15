#include "GraphicsService.h"
#include "easylogging++.h"
#include <stdexcept>

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

void GraphicsService::addToRenderMap(int layer, std::vector<std::pair<GameObject*, SDL_Texture*>> pairs)
{

	// Translate the supplied integer to the layer enumeration
	if (layer > 4)
		throw std::invalid_argument("Layer argument must be a valid layer!");
	Layer rendLayer;
	try {
		switch (layer)
		{
		case 0:
			rendLayer = Layer::BG;
			break;
		case 1:
			rendLayer = Layer::BOARD;
			break;
		case 2:
			rendLayer = Layer::PIECES;
			break;
		case 3:
			rendLayer = Layer::UI;
			break;
		case 4:
			rendLayer = Layer::MENU;
			break;
		default:
			rendLayer = (Layer)5;
		}
		if (rendLayer >= (Layer)5)
		{
			throw std::invalid_argument("Layer argument must be a valid layer!");
		}
	}
	catch (std::invalid_argument& e)
	{
		LOG(ERROR) << e.what() << "\n";
		SDL_QUIT;
	}

	// TODO: Check to see if the objects are already in the render queue

	// Insert elements in render queue according to their chosen layer
	// TODO: finish this logic for every layer. This was a test to make sure this actually worked!
	switch (rendLayer)
	{
	case Layer::MENU:
		_renderMap[Layer::MENU].insert(_renderMap[Layer::MENU].begin(), pairs.begin(), pairs.end());
		break;
	}
	

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

	// This needs to be finished! Right now it only works for the MENU layer.
	// Can probably find a way to trim it down and have it run for all the layers without iterator conflicts.
	std::pair<GameObject*, SDL_Texture*> target;
	int cnt = 0;
	for (int i = 0; i < objects.size(); ++i)
	{
		target = objects.at(i);
		cnt = std::count(_renderMap[Layer::MENU].begin(), _renderMap[Layer::MENU].end(), target);
		if (cnt > 0)
		{
			LOG(INFO) << "Target found! Attempting to find its position in render queue...";
			std::vector<std::pair<GameObject*, SDL_Texture*>>::const_iterator iVect = std::find(_renderMap[Layer::MENU].begin(), _renderMap[Layer::MENU].end(), target);
			if (iVect != _renderMap[Layer::MENU].end())
			{
				_renderMap[Layer::MENU].erase(iVect);
				LOG(INFO) << "Object erased from render queue!";
			}
		} 
		else
		{
			LOG(INFO) << "Object not found in render map!";
		}
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

	std::map<Layer, std::vector<std::pair<GameObject*, SDL_Texture*>>>::iterator mapItr = _renderMap.begin();
	for (mapItr; mapItr != _renderMap.end(); mapItr++)
	{
		for (auto vItr = mapItr->second.begin(); vItr != mapItr->second.end(); vItr++)
		{
			SDL_RenderCopy(renderer, vItr->second, NULL, vItr->first->getDimensions());
		}
	}

	SDL_RenderPresent(renderer);

	//// Render Layer 0
	//std::vector<std::pair<GameObject*, SDL_Texture*>>::iterator vItr;
	//vItr = _renderMap[GraphicsService::BG].begin();
	//for (vItr; vItr != _renderMap[GraphicsService::BG].end(); vItr++)
	//{
	//	SDL_RenderCopy(renderer, vItr->second, NULL, vItr->first->getDimensions());
	//}

	//// Render Layer 1
	//vItr = _renderMap[GraphicsService::BOARD].begin();
	//for (vItr; vItr != _renderMap[GraphicsService::BOARD].end(); vItr++)
	//{
	//	SDL_RenderCopy(renderer, vItr->second, NULL, vItr->first->getDimensions());
	//}

	//// Render Layer 2
	//vItr = _renderMap[GraphicsService::PIECES].begin();
	//for (vItr; vItr != _renderMap[GraphicsService::PIECES].end(); vItr++)
	//{
	//	SDL_RenderCopy(renderer, vItr->second, NULL, vItr->first->getDimensions());
	//}

	//// Render Layer 3
	//for (auto uiItr = _renderMap[GraphicsService::UI].begin(); uiItr != _renderMap[GraphicsService::BG].end(); uiItr++)
	//{
	//	SDL_RenderCopy(renderer, uiItr->second, NULL, uiItr->first->getDimensions());
	//}

	//// Render Layer 4
	//for (auto menuItr = _renderMap[GraphicsService::MENU].begin(); menuItr != _renderMap[GraphicsService::BG].end(); menuItr++)
	//{
	//	SDL_RenderCopy(renderer, menuItr->second, NULL, menuItr->first->getDimensions());
	//}

	

	//std::map<int, std::pair<GameObject*, SDL_Texture*>>::iterator it = _renderMap.begin();
	//for (it; it != _renderMap.end(); it++)
	//{
	//	SDL_RenderCopy(renderer, it->second.second, NULL, it->second.first->getDimensions());
	//}

}


