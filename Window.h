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
	
public:

	//Constructors
	Window(int width = 1920, int height = 1080);

	~Window();

	// ** Methods **

	// Creates the SDL window using the values of the Window wrapper class
	void initWindow();

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

	// Deallocate the window
	void freeWindow();

	/// <summary>
	/// Resizes the window
	/// </summary>
	/// <param name="w">width</param>
	/// <param name="h">height</param>
	void ResizeWindow(int w, int h);
};

