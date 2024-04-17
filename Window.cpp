#include "Window.h"
#include <SDL.h>

/// <summary>
///  Default constructor for a window
/// </summary>
/// <param name="width">The width of the window</param>
/// <param name="height">The height of the window</param>
Window::Window(int width, int height) 
	: windowHeight { height }, windowWidth { width }
{}
