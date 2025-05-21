#include "GraphicsService.h"
#include "easylogging++.h"
#include <stdexcept>
#include <cassert>

GraphicsService::GraphicsService(Window* window) :	

	_window(window), _renderer(new Renderer(window))
{
	// Asserts that there are no existing instances of the Graphics Service
	assert(!_instantiated);
	_instantiated = true;
	LOG(TRACE) << "Graphics Service initialized!";
}

GraphicsService::~GraphicsService()
{
	_instantiated = false;
	LOG(TRACE) << "Graphics Service destructed";
}

Window* GraphicsService::getWindow()
{
	return _window;
}

Renderer* GraphicsService::getRenderer()
{
	return _renderer;
}

bool GraphicsService::compareZ(IDrawable* a, IDrawable* b)
{
	return a->getZ() < b->getZ();
}

void GraphicsService::addToRenderMap(int layer, std::vector<IDrawable*> objects)
{
	// Translate the supplied integer to the layer enumeration
	if (layer > 4)
		throw std::invalid_argument("Layer argument must be a valid layer!\n");
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
			throw std::invalid_argument("Layer argument must be a valid layer!\n");
		}
	}
	catch (std::invalid_argument& e)
	{
		LOG(ERROR) << e.what() << "\n";
		SDL_QUIT;
	}

	if (findInRenderMap(objects).size() == 0)
	{
		// Add objects to the render map if they are not already in the render map
		_renderMap[rendLayer].insert(_renderMap[rendLayer].begin(), objects.begin(), objects.end());
		LOG(DEBUG) << "Objects added to render map!";
		sortRenderMap();
	}
	else
	{
		LOG(DEBUG) << "Objects already in render map!";
	}
}

void GraphicsService::removeFromRenderMap(std::vector<IDrawable*> objects)
{
	std::vector<IDrawable*> findVect{ findInRenderMap(objects) };

	for (int i = 0; i < findVect.size(); ++i)
	{
		IDrawable* target{ findVect.at(i) };
		for (int layer = 0; layer < _renderMap.size(); ++layer)
		{
			std::vector<IDrawable*>::const_iterator iVect = std::find(_renderMap[(Layer)layer].begin(), _renderMap[(Layer)layer].end(), target);
			if (iVect != _renderMap[(Layer)layer].end())
			{
				_renderMap[(Layer)layer].erase(iVect);
				LOG(DEBUG) << "Object erased from render layer " << (Layer)layer << "!";
			}
		}
	}
	LOG(DEBUG) << "No more objects to erase in render queue!";

}

std::vector<IDrawable*> GraphicsService::findInRenderMap(std::vector<IDrawable*> objects)
{
	int cnt = 0;
	
	// vector of IDrawable objects to be returned
	std::vector<IDrawable*> foundVect{};

	for (int i = 0; i < objects.size(); ++i)
	{
		IDrawable* target{ objects.at(i) };
		// Loop for every Layer value in the render map
		for (int layer = 0; layer < _renderMap.size(); ++layer)
			// Start the loop
		{
			cnt = std::count(_renderMap[(Layer)layer].begin(), _renderMap[(Layer)layer].end(), target);
			if (cnt > 0)
			{
				LOG(DEBUG) << "Target found in render layer " << (Layer)layer << "!";
				foundVect.push_back(target);
				LOG(DEBUG) << "Target added to found objects vector!";				
			}
		}
	}
	return foundVect;

}

// Sort the render map by Z-value
void GraphicsService::sortRenderMap()
{
	std::map<Layer, std::vector<IDrawable*>>::iterator mItr;
	std::vector<IDrawable*>::iterator vItr;
	for (mItr = _renderMap.begin(); mItr != _renderMap.end(); ++mItr)
	{
		std::sort(mItr->second.begin(), mItr->second.end(),
			// Lamba defining the comparator
			[](IDrawable* a, IDrawable* b)
			{ return a->getZ() < b->getZ(); });
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

	sortRenderMap();

	std::map<Layer, std::vector<IDrawable*>>::iterator mapItr = _renderMap.begin();
	for (mapItr; mapItr != _renderMap.end(); mapItr++)
	{
		for (auto vItr = mapItr->second.begin(); vItr != mapItr->second.end(); vItr++)
		{
			if ((*vItr)->_draw)
			{
				SDL_RenderCopy(renderer, (*vItr)->getCurrentTexture(), NULL, &(*vItr)->getDrawDimensions());
			}
		}
	}

	SDL_RenderPresent(renderer);

}


