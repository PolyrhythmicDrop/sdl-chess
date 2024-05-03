#pragma once
#include <SDL.h>
#include <stdio.h>
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

	void getWindowSize(int* w, int* h);

	// Deallocate the window
	void freeWindow();

	/// <summary>
	/// Resizes the window
	/// </summary>
	/// <param name="w">width</param>
	/// <param name="h">height</param>
	void ResizeWindow(SDL_Renderer* renderer, int w, int h);
};

