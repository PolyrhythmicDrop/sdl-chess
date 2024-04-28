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

namespace GameContext{

	class GameData
	{
	private:
		// The main window for the current game session
		Window _window;

		// The renderer for the current game session
		Renderer _renderer;

	public:

		// Constructor
		GameData();

		// Deconstructor
		~GameData();
		
		void InitializeGameContext(Window window, Renderer renderer);

	};

}