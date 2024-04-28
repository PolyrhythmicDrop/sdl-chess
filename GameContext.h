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
		const Window* _window;

		// The renderer wrapper for the current game session
		const Renderer* _renderer;

		// The SDL renderer used by the Renderer.
		SDL_Renderer* _sdlRenderer;

		// The SDL window used by the Window.
		SDL_Window* _sdlWindow;

	public:

		// Constructor
		GameContext(Window* window, Renderer* renderer);

		// Deconstructor
		~GameContext();

		SDL_Renderer* getSdlRenderer() const;

		SDL_Window*  getSdlWindow() const;
	};