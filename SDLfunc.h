#pragma once
#include <SDL.h>
#include <SDL_image.h>

class SDLfunc
{
		// Public members
public:
	// The SDL window
	SDL_Window* sdlWindow = NULL;

	// The raw SDL surface
	SDL_Surface* sdlSurface = NULL;

	// The PNG SDL surface
	SDL_Surface* pngSurface = NULL;

	// Constructors
	SDLfunc();

	// Methods
	
	/// <summary>
	/// Initialize SDL
	/// </summary>
	/// <returns>True if initialization was successful, false if not.</returns>
	bool Init();

	/// Closes SDL and frees resources
	void Close();
};

