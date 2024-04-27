#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <array>
#include <iostream>

// Window wrapper class
class Window
{
private:
	
	// Window data
	SDL_Window* _window;
	
	// Window height and width
	int _windowWidth;
	int _windowHeight;

	// Window focus
	bool _mouseFocus;
	bool _keyboardFocus;
	bool _fullscreen;
	bool _minimized;
	

public:

	//Constructors
	Window(int width = 1920, int height = 1080);

	// ** Methods **

	// Set the SDL window value
	void setWindow(SDL_Window* window);
	// Get the SDL window
	SDL_Window* getWindow();

	// Get width for window
	int getWindowWidth();
	// Set width for window
	void setWindowWidth(int width);

	// Get height for window
	int getWindowHeight();
	// Set height for window
	void setWindowHeight(int height);

	// Returns true if window has mouse focus
	bool hasMouseFocus();

	// Returns true if window has keyboard focus
	bool hasKeyboardFocus();

	// Returns true if the window is minimized
	bool isMinimized();

	// Deallocate the window
	void freeWindow();

	void ResizeWindow(std::string& ePress);
};

