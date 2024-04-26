#include "EventSource.h"

EventSource::EventSource()
{};

EventSource::~EventSource() {};

bool EventSource::PollEvents(GameDatabase db)
{
	bool quit = false;
	// While the event queue is not empty
	while (SDL_PollEvent(&_currentEvent) != 0)
	{
		// If the user requests to quit by clicking the X in the window, set quit to true and exit
		if (_currentEvent.type == SDL_QUIT)
		{
			quit = true;
			return quit;
		}
		if (_currentEvent.type == SDL_KEYDOWN)
		{
			switch (_currentEvent.key.keysym.sym)
			{
			case SDLK_q:
				quit = true;
				return quit;
			case SDLK_e:
				SDL_Window* window = db.GetWindow();
				SDL_SetWindowSize(window, 1024, 768);
				break;
			}
		}
	}
	return quit;
}

