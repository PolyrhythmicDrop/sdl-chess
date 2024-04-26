// Main game loop for SDL Chess

#include <stdio.h>
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Window.h"
#include "SDLfunc.h"
#include <algorithm>
#include "Button.h"
#include "Texture.h"



/// <summary>
/// Draws the chessboard.
/// </summary>
/// <param name="window">The window to get dimensions from.</param>
/// <param name="renderer">The renderer.</param>
/// <param name="borderWidth">The width of the border for the chessboard.</param>
static void drawChessboard(Window window, SDL_Renderer* renderer, double borderWidth = 10)
{
	int windowW = window.getWindowWidth();
	int windowH = window.getWindowHeight();
	// Get minimum value between window width and window height to set the board side length
	int minWindowDimension = std::min(windowW, windowH);
	// Set the board side length to the 2/3rds the size of the minimum dimension of the window size
	double boardSideLength = (minWindowDimension * 2 / 3);
	double borderPointerPos = borderWidth / 2;

	SDL_FRect boardBase = { 0, 0, boardSideLength, boardSideLength };
	SDL_FRect boardBorder = { 0, 0, boardSideLength + borderWidth, boardSideLength + borderWidth };
	// Set the width and height of the boardBase and boardBorder rectangles to be the center of the window
	boardBase.x = (windowW / 2) - (boardBase.w / 2);
	boardBase.y = (windowH / 2) - (boardBase.h / 2);
	boardBorder.x = (windowW / 2) - (boardBase.w / 2) - borderPointerPos;
	boardBorder.y = (windowH / 2) - (boardBase.h / 2) - borderPointerPos;

	// Get the side for each square in the board
	float spaceSideLength = (boardBase.w / 8);

	// Create the basic board square variable
	SDL_FRect boardSpace = { 0, 0, spaceSideLength, spaceSideLength };
	SDL_Point boardSpaceStartPoint = { boardBase.x, boardBase.y };
	SDL_Point boardSpacePoint = boardSpaceStartPoint;

	// Draw the board border
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRectF(renderer, &boardBorder);

	// Draw the board base
	SDL_SetRenderDrawColor(renderer, 182, 133, 35, 255);
	SDL_RenderFillRectF(renderer, &boardBase);

	// Draw the chessboard
	// Set the render color to white for the odd board squares
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	// Draw the odd board squares
	for (int i = 1; i <= 4; i++)
	{
		// Draw the first row of odd board squares
		for (int i = 1; i <= 4; i++)
		{
			boardSpace.x = boardSpacePoint.x;
			boardSpace.y = boardSpacePoint.y;
			SDL_RenderFillRectF(renderer, &boardSpace);
			boardSpacePoint.x = boardSpacePoint.x + (spaceSideLength * 2);
		}
		// Move the y value of the draw point down by a space, then the x point over by a space					
		boardSpacePoint.y = boardSpacePoint.y + spaceSideLength;
		boardSpacePoint.x = boardSpacePoint.x - (spaceSideLength * 7);
		// Draw the next row of odd board squares
		for (int i = 1; i <= 4; i++)
		{
			boardSpace.x = boardSpacePoint.x;
			boardSpace.y = boardSpacePoint.y;
			SDL_RenderFillRectF(renderer, &boardSpace);
			boardSpacePoint.x = boardSpacePoint.x + (spaceSideLength * 2);

		}
		boardSpacePoint.x = boardSpacePoint.x - (spaceSideLength * 9);
		boardSpacePoint.y = boardSpacePoint.y + spaceSideLength;
	}

}

// ** Main loop **

int main( int argc, char* args[] )
{
	
	// Initialize the SDL Engine, which contains all my basic SDL functions
	SDLfunc sdlEngine{};

	// Initialize SDL and check if successful
	sdlEngine.Init(SDL_INIT_VIDEO, IMG_INIT_PNG);

		// Create the window instance, using parameters specified by options menu. Default is 1920x1080.
		Window window{};
		int windowW = window.getWindowWidth();
		int windowH = window.getWindowHeight();


		// Generate the SDL window
		window.setWindow(SDL_CreateWindow("SDL Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowW, windowH, SDL_WINDOW_SHOWN ));
		SDL_Window* mainWindow = window.getWindow();
		if (mainWindow == NULL)
		{
			printf("Window could not be created! SDL Error %s\n", SDL_GetError());			
		}
		
		// Initialize the renderer
		SDL_Renderer* mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_ACCELERATED );
		// Set render resolution to match the window
		if (SDL_RenderSetLogicalSize(mainRenderer, windowW, windowH) < 0)
		{
			printf("Failed to set logical render size!\n");
		}
		
		
		// Button class loading test
		Texture textureLoader(mainRenderer);
		Button optionsButton("Options", "images/esc-menu_button-options.png");
		textureLoader.loadTextureFromImage(optionsButton.getButtonPath());
		optionsButton.setButtonTexture(textureLoader.getTexture());
		SDL_Texture* optionsTexture = optionsButton.getButtonTexture();
		optionsButton.setButtonDimensions(0, 0, 300, 100);

		SDL_Rect optionsDestRect = { 0, 0, optionsButton.getButtonWidth(), optionsButton.getButtonHeight() };
		
		if (mainRenderer == NULL)
		{
			printf("Renderer failed to initalize!\n");
		}
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
					if (e.type == SDL_KEYDOWN)
					{
						switch (e.key.keysym.sym)
						{
						case SDLK_q:
							SDL_SetWindowSize(mainWindow, 1024, 768);
							windowW = 1024;
							windowH = 768;
							break;
						case SDLK_e:
							SDL_SetWindowSize(mainWindow, 1920, 1080);
							windowW = 1920;
							windowH = 1080;		
							break;
						case SDLK_ESCAPE:
							quit = true;
							break;
						}

					}
				}
				
				
				// Fill the screen with white
				SDL_SetRenderDrawColor(mainRenderer, 100, 100, 100, 255);
				SDL_RenderClear(mainRenderer);

				drawChessboard(window, mainRenderer);				

				SDL_RenderCopy(mainRenderer, optionsTexture, NULL, &optionsDestRect);
				

				
				// Update screen
				SDL_RenderPresent(mainRenderer);

			}
		}

	
		sdlEngine.Close();



	return 0;
};