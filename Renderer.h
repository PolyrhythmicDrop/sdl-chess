#pragma once
#include "Window.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

class Renderer
{
private:
	SDL_Renderer* _renderer;

public:

	// Default constructor
	Renderer(Window* window);

	// Deconstructor
	~Renderer();

	SDL_Renderer* GetRenderer();
};

