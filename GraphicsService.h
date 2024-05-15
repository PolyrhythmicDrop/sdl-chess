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

	Window* getWindow();

	/// <summary>
	/// Returns the renderer wrapper class.
	/// </summary>
	/// <returns></returns>
	Renderer* getRenderer();

	void addToRenderMap(int layer, std::vector<std::pair<GameObject*, SDL_Texture*>> pairs);

	void removeFromRenderMap(std::vector<std::pair<GameObject*, SDL_Texture*>> objects);

	std::vector<std::pair<GameObject*, SDL_Texture*>> findInRenderMap(std::vector<std::pair<GameObject*, SDL_Texture*>> objects);

	void render();

private:
	
	Renderer* _renderer;
	Window* _window;

	/// <summary>
	/// Map containing all the objects and textures to render. These objects are ordered by layer within the map, and by Z within the object vector.
	/// </summary>
	std::map<Layer, std::vector<std::pair<GameObject*, SDL_Texture*>>> _renderMap;

	static bool _instantiated;

};

