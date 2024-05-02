#pragma once
#include "Window.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

class Renderer
{
private:
	SDL_Renderer* _sdlRenderer;

public:

	// Constructor, initializes the renderer with several SDL flags enabled: SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC. To change these, re-do the constructor.
	Renderer(Window* window);

	// Deconstructor
	~Renderer();

	SDL_Renderer* GetRenderer();
};

