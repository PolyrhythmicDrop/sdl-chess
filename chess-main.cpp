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
	sdlEngine.Init();

	// Initialize SDL IMG and check if successful
	sdlEngine.InitIMG(IMG_INIT_PNG);

		// Create the window instance, using parameters specified by options menu. Default is 640x480.
		Window window{1080, 720};
		// Generate the SDL window
		SDL_Window* mainWindow = sdlEngine.createWindow(window.getWindowWidth(), window.getWindowHeight());
		// Initialize the renderer
		SDL_Renderer* mainRenderer = sdlEngine.createRenderer(mainWindow, SDL_RENDERER_ACCELERATED, 255, 255, 255, 255);
		// Set render resolution to match the window
		if (SDL_RenderSetLogicalSize(mainRenderer, window.getWindowWidth(), window.getWindowHeight()) < 0)
		{
			printf("Failed to set logical render size!\n");
		}
		// Load media
		std::string imgPath = "images/chessboard.png";
		SDL_Texture* loadedTexture = IMG_LoadTexture(mainRenderer, imgPath.c_str());
		if (!loadedTexture)
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

				// Create rectangle to center
				SDL_Rect centerRect;
				centerRect.x = window.windowWidth / 8;
				centerRect.y = 0;
				centerRect.w = window.windowWidth;
				centerRect.h = window.windowHeight;

				// Clear the screen with the render color
				SDL_RenderClear(mainRenderer);

				// Render texture to screen
				SDL_RenderCopy(mainRenderer, loadedTexture, NULL, NULL);

				// Update screen
				SDL_RenderPresent(mainRenderer);

				/*
				// Apply/blit the optimized PNG image that we loaded
				SDL_BlitSurface(sdlEngine.pngSurface, NULL, sdlEngine.windowSurface, &centerRect);

				// Update the surface after blitting
				SDL_UpdateWindowSurface(sdlEngine.sdlWindow);
				*/
			}
		}

	sdlEngine.Close();



	return 0;
};