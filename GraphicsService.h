#pragma once
#include <iostream>
#include <SDL.h>
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

	static bool _instantiated;


public:

	GraphicsService(Window* window);

	~GraphicsService();

	virtual Window* getWindow();

	virtual Renderer* getRenderer();

	virtual void addToQueue();

	virtual void removeFromQueue();

	virtual void render();

};

