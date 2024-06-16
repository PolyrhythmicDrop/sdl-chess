#pragma once
#include "IGraphics.h"


/// <summary>
/// Service class to handle graphics. Container for Window and Renderer, contains a draw queue, and has functions to draw the queue and return the window and renderer.
/// </summary>
class GraphicsService: public IGraphics
{

public:
	
	GraphicsService(Window* window);

	~GraphicsService();

	// Custom comparator for render map
	bool compareZ(IDrawable* a, IDrawable* b);

	Window* getWindow();

	/// <summary>
	/// Returns the renderer wrapper class.
	/// </summary>
	/// <returns></returns>
	Renderer* getRenderer();

	void addToRenderMap(int layer, std::vector<IDrawable*> objects);

	void removeFromRenderMap(std::vector<IDrawable*> objects);

	std::vector<IDrawable*> findInRenderMap(std::vector<IDrawable*> objects);

	// Sorts the render map by Z-value.
	void sortRenderMap();

	void render();

private:
	
	Renderer* _renderer;
	Window* _window;

	/// <summary>
	/// Map containing all the objects and textures to render. These objects are ordered by layer within the map, and by Z within the object vector.
	/// </summary>
	/*std::map<Layer, std::vector<std::pair<GameObject*, SDL_Texture*>>> _renderMap;*/

	std::map<Layer, std::vector<IDrawable*>> _renderMap;

	static bool _instantiated;

};

