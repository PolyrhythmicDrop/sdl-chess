#include "EventManager.h"
#include <SDL.h>
#include <list>
#include <utility>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std::placeholders;


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
			break;
		}
		if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				*quit = true;
				break;
			case SDLK_e:
				_eventName = "E";				
				break;
			case SDLK_q:
				_eventName = "Q";		
				break;
			}
			Event();
		}		
	}
}

void EventManager::Subscribe(const std::string event, std::function<void(int, int)> callback)
{
	// Add an event and an associated callback function to the subscriber list.
	m_subscribers[event].push_back(callback);
}

void EventManager::Publish(std::string event)
{	
	int w = 0;
	int h = 0;
	for (auto& e : m_subscribers[event])
	{
		e(w, h);
	}
}

void EventManager::Event()
{
	Publish(_eventName);
}