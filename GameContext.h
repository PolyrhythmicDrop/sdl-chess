#pragma once
#include "Renderer.h"
#include "Window.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

	class GameContext
	{
	private:
		// The main window for the current game session
		Window _window;

		// The renderer wrapper for the current game session
		Renderer _renderer;

	public:

		// Constructor
		GameContext(Window window, Renderer renderer);

		// Deconstructor
		~GameContext();

	};