#include "EventManager.h"
#include "GameContext.h"
#include "GraphicsService.h"
#include "SceneEscMenu.h"
#include "ProgramStateMachine.h"
#include "easylogging++.h"
#include "GameStateMachine.h"
#include "GameScene.h"


// Initialize static variables
INITIALIZE_EASYLOGGINGPP;
int GameObject::gameObjectCount = 0;
bool GameContext::_instantiated = false;
bool ProgramStateMachine::_instantiated = false;
bool GraphicsService::_instantiated = false;
bool GameStateMachine::_instantiated = false;
bool GameScene::_instantiated = false;
IGraphics* ServiceLocator::_graphicsService;
NullGraphicsService ServiceLocator::_nullGraphicsService;

void initializeLogging()
{
	// Logging configurations
	el::Configurations defaultConf;
	defaultConf.setToDefault();
	defaultConf.set(el::Level::Info, el::ConfigurationType::Format, "%datetime | %func \n%msg\n");
	defaultConf.set(el::Level::Trace, el::ConfigurationType::Format, "%fbase | %line \n%msg\n");
	defaultConf.set(el::Level::Debug, el::ConfigurationType::Format, "%datetime | %fbase\n | %func \n | %line \n%msg");
	defaultConf.set(el::Level::Info, el::ConfigurationType::ToFile, "true");
	defaultConf.set(el::Level::Trace, el::ConfigurationType::ToFile, "true");
	defaultConf.set(el::Level::Debug, el::ConfigurationType::ToFile, "true");
	defaultConf.set(el::Level::Debug, el::ConfigurationType::ToStandardOutput, "false");
	defaultConf.set(el::Level::Info, el::ConfigurationType::Filename, "chess-log.log");
	defaultConf.set(el::Level::Trace, el::ConfigurationType::Filename, "chess-log.log");
	defaultConf.set(el::Level::Debug, el::ConfigurationType::Filename, "chess-debug.log");
	el::Loggers::reconfigureLogger("default", defaultConf);
}

// ** Main loop **

int main( int argc, char* args[] )
{	
	initializeLogging();

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
	ProgramStateMachine psm;

	// Constants for the game loop
	const int fps = 60;
	const int skipTicks = 1000 / fps;
	Uint64 nextGameTick = SDL_GetTicks64();

	int sleepTime = 0;

	/* 
	******************************
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
	*******************************
	*/ 

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