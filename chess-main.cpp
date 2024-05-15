#include "EventManager.h"
#include "GameContext.h"
#include "GraphicsService.h"
#include "SceneEscMenu.h"
#include "GameStateMachine.h"
#include "easylogging++.h"
#include "Chessboard.h"
#include "SquareGraphicsComponent.h"


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
INITIALIZE_EASYLOGGINGPP;
int GameObject::gameObjectCount = 0;
bool GameContext::_instantiated = false;
bool GameStateMachine::_instantiated = false;
bool GraphicsService::_instantiated = false;
IGraphics* ServiceLocator::_graphicsService;
NullGraphicsService ServiceLocator::_nullGraphicsService;


// ** Main loop **

int main( int argc, char* args[] )
{	
	// Logging configurations
	el::Configurations defaultConf;
	defaultConf.setToDefault();
	defaultConf.set(el::Level::Info, el::ConfigurationType::Format, "%datetime | %func \n%msg");
	defaultConf.set(el::Level::Info, el::ConfigurationType::ToFile, "true");
	defaultConf.set(el::Level::Info, el::ConfigurationType::Filename, "chess-log.log");
	el::Loggers::reconfigureLogger("default", defaultConf);

	// Initialize the game context
	GameContext gc;
	
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
	EventManager& eManager = EventManager::getEventManagerInstance();

	// Initialize the game state machine
	GameStateMachine gsm;

	// Constants for the game loop
	const int fps = 60;
	const int skipTicks = 1000 / fps;
	Uint64 nextGameTick = SDL_GetTicks64();

	int sleepTime = 0;

	// Square overlay testing
	Chessboard board;
	board.buildChessboard();
			
	// Test adding objects to render queue
	std::vector<std::pair<GameObject*, SDL_Texture*>> testVect;
	std::vector<std::vector<Square>> boardGrid = board.getBoardGrid();

	LOG(INFO) << "The size of the board grid is: " << boardGrid.size() << " rows and " << boardGrid[0].size() << " columns.";

	// Debug: get the coordinates for each item in the grid and put them in the log
	for (int row = 0; row < boardGrid.size(); ++row)
	{
		LOG(INFO) << "";
		for (int column = 0; column < boardGrid[row].size(); ++column)
		{
			LOG(INFO) << "[ " << boardGrid[row][column].getName() << " ]\nX: " << boardGrid[row][column].getX() << "\nY: " << boardGrid[row][column].getY() << "\nZ: " << boardGrid[row][column].getZ() << "\nW: " << boardGrid[row][column].getWidth() << "\nH: " << boardGrid[row][column].getHeight();
		}
	}
	
	

	for (int row = 0; row < boardGrid.size(); ++row)
	{
		for (int column = 0; column < boardGrid[row].size(); ++column)
		testVect.push_back(std::pair<GameObject*, SDL_Texture*>(&boardGrid[row][column], boardGrid[row][column].getGraphicsComponent()->getSdlTexture()));
	}	

	ServiceLocator::getGraphics().addToRenderMap(1, testVect);
	
		
	// Main quit flag for the loop
	bool quit = false;				

	// While the application is running...
	while (!quit)
	{
		// Handle events
		eManager.HandleEvents(&quit);
								
		// Render graphics
		ServiceLocator::getGraphics().render();

		// Adjust time step
		nextGameTick += skipTicks;
		sleepTime = nextGameTick - SDL_GetTicks64();
		if (sleepTime >= 0)
		{
			SDL_Delay(sleepTime);
		}
		
	}
		
sdlEngine.Close();

	return 0;
};