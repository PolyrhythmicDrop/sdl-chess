#pragma once
#include "Button.h"
#include "EventManager.h"
#include "Renderer.h"
#include "Texture.h"
#include "Window.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

	class GameContext
	{
	private:
		// The main window for the current game session
		SDL_Window* _window;

		// The renderer wrapper for the current game session
		Renderer _renderer;

	public:

		// Constructor
		GameContext(SDL_Window* window, Renderer renderer);

		// Deconstructor
		~GameContext();

	};