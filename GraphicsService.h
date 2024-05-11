#pragma once
#include "IGraphics.h"
#include <cassert>

/// <summary>
/// Service class to handle graphics. Container for Window and Renderer, contains a draw queue, and has functions to draw the queue and return the window and renderer.
/// </summary>
class GraphicsService: public IGraphics
{
private:
	Renderer* _renderer;
	Window* _window;

	std::map<int, std::pair<GameObject*, SDL_Texture*>> _renderMap;

	std::vector<Square*> _squareDrawV;

	static bool _instantiated;


public:

	GraphicsService(Window* window);

	~GraphicsService();

	virtual Window* getWindow();

	virtual Renderer* getRenderer();

	virtual void addToRenderMap(std::map<int, std::pair<GameObject*, SDL_Texture*>> map);

	virtual void removeFromRenderMap(std::vector<int> zValues);

	virtual void render();

};

