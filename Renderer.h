#pragma once
#include "GameContext.h"
#include "Texture.h"
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
	Renderer();

	// Deconstructor
	~Renderer();

	void SetRenderer();
};

