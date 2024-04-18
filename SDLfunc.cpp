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
	return success;
}

SDL_Window* SDLfunc::createWindow(int width, int height)
{
	// Window creation flag
	bool success = true;
	// Create an SDL window
	sdlWindow = SDL_CreateWindow("SDL Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
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
	return sdlWindow;
}

bool SDLfunc::loadMedia()
{
	// Loading success flag
	bool success = true;

	// Load the PNG image to a surface
	pngSurface = loadSurface("images/chessboard.png");

	// Error checking for load media
	if (pngSurface == NULL)
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}

	return success;
}

SDL_Surface* SDLfunc::loadSurface(std::string path)
{
	// The final, optimized image, loaded to a surface
	SDL_Surface* optimizedSurface = NULL;

	// Load image 
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		optimizedSurface = SDL_ConvertSurface(loadedSurface, sdlSurface->format, 0);
		// Error checking for surface optimization
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		// Free old loaded surface, which was unoptimized
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
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
