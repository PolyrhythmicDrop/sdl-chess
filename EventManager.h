#pragma once
#include <SDL.h>
#include "Window.h"



class EventManager
{
public: 
	SDL_Event e;

	/// <summary>
	/// Default constructor for the Event Manager
	/// </summary>
	EventManager();

	/// <summary>
	/// Controls the event loop of polling for events.
	/// </summary>
	/// <param name="e">The event variable to use in the event queue</param>
	/// <param name="quit">Flag to quit the whole program and the event loop.</param>
	void EventLoop(bool* quit);

};

