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
	
	// The window
	SDL_Window* _window;
	
	// Window height and width
	int _windowWidth;
	int _windowHeight;

public:

	//Constructors
	Window(int width = 640, int height = 480);

	// Methods

	// Set the SDL window value
	void setWindow(SDL_Window* window);
	// Get the SDL window
	SDL_Window* getWindow();

	// Window height and width
	int getWindowWidth();
	void setWindowWidth(int width);

	// Get window height
	int getWindowHeight();
	void setWindowHeight(int height);


};

