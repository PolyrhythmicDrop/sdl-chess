#include "Window.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <array>
#include <iostream>

/// <summary>
///  Default constructor for a window. Set width and height with default value, then everything else gets initialized.
/// </summary>
/// <param name="width">The width of the window</param>
/// <param name="height">The height of the window</param>
Window::Window(int width, int height)
	: _windowWidth{ width },
	_windowHeight{ height }
{
	_window = NULL;
	_mouseFocus = false;
	_keyboardFocus = false;
	_fullscreen = false;
	_minimized = false;
}

void Window::setWindow(SDL_Window* window)
{
	_window = window;
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

bool Window::hasMouseFocus()
{
	return _mouseFocus;
}

bool Window::hasKeyboardFocus()
{
	return _keyboardFocus;
}

bool Window::isMinimized()
{
	return _minimized;
}

void Window::freeWindow()
{
	if (_window != NULL)
	{
		SDL_DestroyWindow(_window);
	}
	_mouseFocus = false;
	_keyboardFocus = false;
	_windowWidth = 0;
	_windowHeight = 0;
}

void Window::ResizeWindow(std::string& event)
{
	SDL_SetWindowSize(_window, 1024, 768);
	_windowWidth = 1024;
	_windowHeight = 768;
}
