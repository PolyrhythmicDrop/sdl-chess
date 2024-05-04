#pragma once
#include "IGraphics.h"
#include <cassert>
#include <iostream>

/// <summary>
/// Service class to handle graphics. Container for Window and Renderer, contains a draw queue, and has functions to draw the queue and return the window and renderer.
/// </summary>
class GraphicsService: public IGraphics
{
private:
	Renderer* _renderer;
	Window* _window;

	std::map<GameObject*, SDL_Texture*> _renderMap;

	static bool _instantiated;


public:

	GraphicsService(Window* window);

	~GraphicsService();

	virtual Window* getWindow();

	virtual Renderer* getRenderer();

	virtual void addToRenderMap(std::map<GameObject*, SDL_Texture*> map);

	virtual void removeFromQueue();

	virtual void render();

};

