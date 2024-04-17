#include "SDLfunc.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "Window.h"


// ** Constructors **

// Default constructor
SDLfunc::SDLfunc() {};

// ** Methods **

bool SDLfunc::Init()
{
	/// Initialization flag
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Instantiate the Window class
		Window gWindow{};

		// Create an SDL window
		sdlWindow = SDL_CreateWindow("SDL Chess", 0, 0, gWindow.windowWidth, gWindow.windowHeight, SDL_WINDOW_SHOWN);
		// Error handling for SDL window creation
		if (sdlWindow == NULL)
		{
			printf("Window could not be created! SDL Error %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			// PNG error handling
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				success = false;
			}
			else
			{
				// Get the surface of the new SDL window
				sdlSurface = SDL_GetWindowSurface(sdlWindow);
			}

		}
	}
	return success;
}

void SDLfunc::Close()
{
	// Free the loaded PNG image
	SDL_FreeSurface(pngSurface);
	pngSurface = NULL;

	// Destroy the window
	SDL_DestroyWindow(sdlWindow);
	sdlWindow = NULL;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
