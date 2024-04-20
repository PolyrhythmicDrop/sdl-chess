#include "Window.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <array>
#include <iostream>

/// <summary>
///  Default constructor for a window
/// </summary>
/// <param name="width">The width of the window</param>
/// <param name="height">The height of the window</param>
Window::Window(int width, int height) 
	: _windowWidth{ width }, _windowHeight { height }, _window { NULL }
{}

void Window::setWindow(SDL_Window* window)
{
	window = _window;
}

SDL_Window* Window::getWindow()
{
	return _window;
}

int Window::getWindowWidth()
{
	return _windowWidth;
}

void Window::setWindowWidth(int width)
{
	if (width > 0)
	{
		_windowWidth = width;
	}
	else
	{
		printf("Cannot set window width to less than 0!\n");
	}	
}

int Window::getWindowHeight()
{
	return _windowHeight;
}

void Window::setWindowHeight(int height)
{
	if (height > 0)
	{
		_windowHeight = height;
	}
	else
	{
		printf("Cannot set window height to less than 0!\n");
	}
}
