#include "EventManager.h"
#include "GameContext.h"
#include "GraphicsService.h"
#include "SceneEscMenu.h"


/// <summary>
/// Draws the chessboard.
/// </summary>
/// <param name="window">The window to get dimensions from.</param>
/// <param name="renderer">The renderer.</param>
/// <param name="borderWidth">The width of the border for the chessboard.</param>
/*static void drawChessboard(Window window, SDL_Renderer* renderer, double borderWidth = 10)
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

}*/

// Initialize static variables
int GameObject::gameObjectCount = 0;
bool GameContext::_instantiated = false;
bool GraphicsService::_instantiated = false;
IGraphics* ServiceLocator::_graphicsService;
NullGraphicsService ServiceLocator::_nullGraphicsService;


// ** Main loop **

int main( int argc, char* args[] )
{	

	// Initialize the game context
	GameContext gc;
	std::vector<GameObject*> gameObjects;
	gameObjects.reserve(50);
	
	// Initialize the SDL Engine
	SDLfunc sdlEngine{};

	// Initialize SDL and check if successful
	sdlEngine.Init();	

	// Initialize SDL IMG and check if successful
	sdlEngine.InitIMG(IMG_INIT_PNG);

	// Initialize the Service Locator and call initialize to set it to the null provider
	ServiceLocator locator{};
	locator.initialize();

	// Instantiate the Window instance in 1920x1080, the native resolution.
	Window window{};
	// Generate the SDL window
	window.initWindow();
	// Initialize the graphics service using the window
	GraphicsService graphics{ &window };

	// Set the service locator to provide the graphics service
	locator.provide(&graphics);


		
	// Initialize the event manager
	EventManager eManager;		
	// ** Event subscriptions **			
	eManager.Subscribe("E", std::bind(&Window::ResizeWindow, &window, ServiceLocator::getGraphics().getRenderer()->GetRenderer(), 1920, 1080));
	eManager.Subscribe("Q", std::bind(&Window::ResizeWindow, &window, ServiceLocator::getGraphics().getRenderer()->GetRenderer(), 1024, 768));		

	// Scene building test
	SceneEscMenu escMenu;
	escMenu.changeState();
	

		
			// Main quit flag for the loop
			bool quit = false;				


			// While the application is running...
			while (!quit)
			{
				eManager.EventLoop(&quit);
				
				
				// Attempt the render command to render the escape menu scene
				ServiceLocator::getGraphics().render();
		


	
				
								
				
				// Fill the screen with white
				//SDL_SetRenderDrawColor(gc.getSdlRenderer(), 100, 100, 100, 255);

				//SDL_RenderClear(gc.getSdlRenderer());

				// Commenting out to stop rendering
				// SDL_RenderCopy(gc.getSdlRenderer(), optionsTexture, NULL, &destRect);

				// Substitute this with an image of a chessboard, it'll be easier to work with!
				// drawChessboard(window, mainRenderer);								
			

				// Update screen
				//SDL_RenderPresent(gc.getSdlRenderer());
				
			}
		

	
		sdlEngine.Close();

	return 0;
};