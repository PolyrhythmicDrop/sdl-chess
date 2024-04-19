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

		// Get values for rect, renderer and window
		/*
		int loadedTextureW;
		int loadedTextureH;
		SDL_QueryTexture(loadedTexture, NULL, NULL, &loadedTextureW, &loadedTextureH);
		float renderScaleX;
		float renderScaleY;
		SDL_RenderGetScale(mainRenderer, &renderScaleX, &renderScaleY);
		int windowW;
		int windowH;
		SDL_GetWindowSize(mainWindow, &windowW, &windowH);

		

		// Create rectangle for the chessboard texture that is set in the middle of the window, no matter the size of the window.
		SDL_Rect centerRect;
		centerRect.x = 0;
		centerRect.y = 0;
		centerRect.w = loadedTextureW;
		centerRect.h = loadedTextureH;

		std::cout << "texture width and height:\n" << loadedTextureW << "\n" << loadedTextureH << "\n";
		std::cout << "render scale X and Y:\n" << renderScaleX << "\n" << renderScaleY << "\n";
		std::cout << "window size width and height:\n" << windowW << "\n" << windowH << "\n";
		std::cout << "Rectangle dimensions:\n" << "X: " << centerRect.x << "\n" << "Y: " << centerRect.y << "\nW: ";
		*/

		
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

				// Clear the screen with the render color
				SDL_RenderClear(mainRenderer);

				// Render texture to screen
				SDL_RenderCopy(mainRenderer, loadedTexture, NULL, &centerRect);

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