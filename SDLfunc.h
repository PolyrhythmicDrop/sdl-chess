#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

class SDLfunc
{
		// Public members
public:
	// The SDL window
	SDL_Window* sdlWindow = NULL;

	// The SDL surface contained by the window
	SDL_Surface* sdlSurface = NULL;

	// The currently displayed PNG surface
	SDL_Surface* pngSurface = NULL;

	// Constructors
	SDLfunc();

	// Methods
	
	/// <summary>
	/// Initialize SDL
	/// </summary>
	/// <returns>True if initialization was successful, false if not.</returns>
	bool Init();

	/// <summary>
	/// Loads up a media file to be passed to loadSurface().
	/// </summary>
	/// <returns></returns>
	bool loadMedia();

	/// <summary>
	/// Loads media at the specified path to a surface
	/// </summary>
	/// <param name="path">The media path</param>
	/// <returns></returns>
	SDL_Surface* loadSurface(std::string path);

	/// Closes SDL and frees resources
	void Close();
};

