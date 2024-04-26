#pragma once
#include "Button.h"
#include "Texture.h"
#include "Window.h"
#include <array>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>

using namespace std;

/// <summary>
/// Contains all the data for the game, including button locations and names, piece locations, board coordinates, etc.
/// </summary>
class GameDatabase : Button, Window
{
private:
	map<string, struct buttonPos> _buttonPosition;
	SDL_Window* _mainWindow;
	

public:
	
	/// <summary>
	/// Constructor for the game database
	/// </summary>
	GameDatabase(SDL_Window* window);

	~GameDatabase();

	/// <summary>
	/// Adds a button's name and position to the map of coordinates
	/// </summary>
	/// <param name="name">Button name</param>
	/// <param name="button">The button object to add</param>
	void AddButton(string name, Button button);

	SDL_Window* GetWindow();

	
	
};

