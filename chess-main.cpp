// Main game loop for SDL Chess

#include <stdio.h>
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Window.h"
#include "SDLfunc.h"


// ** Main loop **

int main( int argc, char* args[] )
{
	// Initialize the SDL Engine, which contains all my basic SDL functions
	SDLfunc sdlEngine{};

	// Initialize SDL and check if successful
	if (!sdlEngine.Init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		// Load media
		if (!sdlEngine.loadMedia())
		{
			printf("Failed to load media!\n");
		}
		// Main blitting and updating loop with event handler begins
		else
		{
			
			// Main loop flag
			bool quit = false;

			// SDL Event Handler
			SDL_Event e;

			// While the application is running...
			while (!quit)
			{
				// While the event queue is empty
				while (SDL_PollEvent( &e ) != 0)
				{
					// If the user requests to quit by clicking the X in the window, set quit to true and exit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}

				// Apply/blit the optimized PNG image that we loaded
				SDL_BlitSurface(sdlEngine.pngSurface, NULL, sdlEngine.sdlSurface, NULL);

				// Update the surface after blitting
				SDL_UpdateWindowSurface(sdlEngine.sdlWindow);
			}
		}
	}

	sdlEngine.Close();



	return 0;
};