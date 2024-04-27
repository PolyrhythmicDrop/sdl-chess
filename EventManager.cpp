#include "EventManager.h"
#include <SDL.h>
#include <list>
#include <utility>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>


EventManager::EventManager()
{
	SDL_PeepEvents(&e, 1, SDL_PEEKEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT);
	_eventName = "";
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
			case SDLK_e:
				_eventName = "E Press";
				
			}			
		}
	}
}

void EventManager::Subscribe(const std::string event, std::function<void(std::string&)> callback)
{
	// Add an event and an associated callback function to the subscriber list.
	m_subscribers[event].push_back(callback);
}

void EventManager::Publish(std::string event)
{
	std::string text = "A button was pressed!";
	std::string& textPntr = text;
	for (auto& e : m_subscribers[event])
	{
		e(textPntr);
	}
}

void EventManager::Event(std::string event)
{
	Publish(event);
}