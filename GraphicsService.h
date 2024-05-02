#pragma once
#include <iostream>
#include <SDL.h>
#include "Renderer.h"
#include "Window.h"
#include <cassert>

class GraphicsService
{
private:
	Renderer* _renderer;	
	Window* _window;

	static bool _instantiated;

public:

	GraphicsService(Window* window);

	~GraphicsService();

	Window* getWindow();

	Renderer* getRenderer();

	void removeFromQueue();

	void drawQueue();

};

