#include "Window.h"

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
	std::cout << "Window wrapper initialized!\n";
}

Window::~Window()
{
	freeWindow();
	std::cout << "Window wrapper destructed!\n";
}

void Window::initWindow()
{
	_window = SDL_CreateWindow("SDL Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _windowWidth, _windowHeight, SDL_WINDOW_SHOWN);
}

SDL_Window* Window::getWindow()
{
	return _window;
}

void Window::getWindowSize(int* w, int* h)
{
	SDL_GetWindowSize(_window, w, h);
}

void Window::freeWindow()
{
	if (_window != NULL)
	{
		SDL_DestroyWindow(_window);
	}
	_windowWidth = 0;
	_windowHeight = 0;
}

void Window::ResizeWindow(SDL_Renderer* renderer, int w, int h)
{
	SDL_SetWindowSize(_window, w, h);
	_windowWidth = w;
	_windowHeight = h;	
	SDL_RenderPresent(renderer);
	std::cout << "Window resized!\n";
}
