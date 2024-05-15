#pragma once
#include "IGraphics.h"
#include <cassert>

/// <summary>
/// Service class to handle graphics. Container for Window and Renderer, contains a draw queue, and has functions to draw the queue and return the window and renderer.
/// </summary>
class GraphicsService: public IGraphics
{

public:
	
	GraphicsService(Window* window);

	~GraphicsService();

	// Custom comparator for render map
	bool compareZ(std::pair<GameObject*, SDL_Texture*> a, std::pair<GameObject*, SDL_Texture*> b);

	virtual Window* getWindow();

	virtual Renderer* getRenderer();

	virtual void addToRenderMap(int layer, std::vector<std::pair<GameObject*, SDL_Texture*>> pairs);

	virtual void removeFromRenderMap(std::vector<std::pair<GameObject*, SDL_Texture*>> objects);

	virtual void render();

private:
	
	Renderer* _renderer;
	Window* _window;

	// New render map. Layer = key. Each layer has a vector of pairs, which should be organized by Z.
	std::map<Layer, std::vector<std::pair<GameObject*, SDL_Texture*>>> _renderMap;

	// std::map<int, std::pair<GameObject*, SDL_Texture*>> _renderMap;

	static bool _instantiated;

};

