#pragma once
#include <SDL.h>
#include "Window.h"


class EventManager
{
public: 

	EventManager(){};

	void EventLoop(SDL_Event e, bool *quit)
	{
		// While the event queue is empty
		while (SDL_PollEvent(&e) != 0)
		{
			// If the user requests to quit by clicking the X in the window, set quit to true and exit
			if (e.type == SDL_QUIT)
			{
				*quit = true;
			}
			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{				
				case SDLK_ESCAPE:
					*quit = true;
					break;				
				}
				

			}
		}
	}

};

