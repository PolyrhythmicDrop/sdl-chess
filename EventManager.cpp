#include "EventManager.h"
#include <SDL.h>

EventManager::EventManager()
{
	SDL_PeepEvents(&e, 1, SDL_PEEKEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT);
};

void EventManager::EventLoop(bool* quit)
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