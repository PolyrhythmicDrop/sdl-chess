#include "GameDatabase.h"


/// <summary>
/// Constructor
/// </summary>
GameDatabase::GameDatabase(SDL_Window* window) : 
	_buttonPosition()
{
	// Clears all buttons from the map on initialization
	_buttonPosition.clear();
	_mainWindow = window;
};

GameDatabase::~GameDatabase() {};

void GameDatabase::AddButton(string name, Button button)
{
	// Rename the button position map to a more digestible name
	auto posMap = _buttonPosition;
	// Add the button position from the button class to a variable	
	auto pos = button.buttonPos;
	// Insert the button and its position into the map
	posMap.insert({ button.getButtonName(), pos });
};

SDL_Window* GameDatabase::GetWindow()
{
	return _mainWindow;
}



