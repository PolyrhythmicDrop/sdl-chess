#pragma once
#include <SDL.h>
#include "GameDatabase.h"


class EventSource
{
private:
	SDL_Event _currentEvent;


public:

	EventSource();

	~EventSource();

	bool PollEvents(GameDatabase db);
};

