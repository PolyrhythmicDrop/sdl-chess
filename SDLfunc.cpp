#include "SDLfunc.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "Window.h"
#include <array>
#include <iostream>


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

bool SDLfunc::InitIMG(IMG_InitFlags flags)
{
	/// Initialization flag
	bool success = true;
	/// Flags for image type
	int imgFlags = flags;
	/// Initialize loading using the type specified in flags argument
	if (!imgFlags)
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		success = false;
	}

	return success;
}


std::array<Uint8,4> SDLfunc::colorConverter(int r, int g, int b, int a)
{
	// Create an array from the arguments
	std::array<int, 4> intArray = { r, g, b, a };
	std::array<Uint8, 4> uint8Array;

	// Convert integers in array to uint8 and add to uint8 array
	for (int i = 0; i < 4; i++)
	{
		uint8Array[i] = intArray[i];
	}

	return uint8Array;
}

SDL_Renderer* SDLfunc::createRenderer(SDL_Window* window, SDL_RendererFlags flags, int r, int g, int b, int a)
{
	windowRenderer = SDL_CreateRenderer(window, -1, flags);
	if (windowRenderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());		
	}
	else
	{
		// Convert integer RGBA to Uint8 RGBA
		std::array<Uint8, 4> colorArray = SDLfunc::colorConverter(r, g, b, a);
		Uint8 convR = colorArray[0];
		Uint8 convG = colorArray[1];
		Uint8 convB = colorArray[2];
		Uint8 convA = colorArray[3];
		//Initialize renderer color
		SDL_SetRenderDrawColor(windowRenderer, convR, convG, convB, convA);
	}

	return windowRenderer;
}


bool SDLfunc::loadMedia()
{
	// Loading success flag
	bool success = true;

	// Load the PNG image to a surface
	pngSurface = loadSurface("assets/chessboard.png");

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
		// Get surface from the SDL Window
		windowSurface = SDL_GetWindowSurface(sdlWindow);
		optimizedSurface = SDL_ConvertSurface(loadedSurface, windowSurface->format, 0);
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
	// Free the loaded PNG image, if any
	SDL_FreeSurface(pngSurface);
	pngSurface = NULL;

	// Free the loaded texture
	SDL_DestroyTexture(loadedTexture);
	loadedTexture = NULL;

	// Destroy the window
	SDL_DestroyRenderer(windowRenderer);
	SDL_DestroyWindow(sdlWindow);
	sdlWindow = NULL;
	windowRenderer = NULL;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
