#include "EventManager.h"
#include "SceneEscMenu.h"


EventManager::EventManager()
{
	SDL_PeepEvents(&e, 1, SDL_PEEKEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT);	
};

void EventManager::HandleEvents(bool* quit)
{
	// While the event queue is empty
	while (SDL_PollEvent(&e) != 0)
	{
		// If the event type is a quit, end the game.
		if (e.type == SDL_QUIT)
		{
			*quit = true;
		}
		Event();
	}
	return;
}

void EventManager::Subscribe(SDL_EventType type, eventCallback callback)
{
	// Add an event type and an associated callback function to the subscriber list.
	_subscribedCallbacks[type].push_back(callback);
}

void EventManager::Unsubscribe(SDL_EventType type)
{
	_subscribedCallbacks[type].clear();
}

void EventManager::Publish(SDL_Event event)
{	
	for (auto& cb : _subscribedCallbacks[static_cast<SDL_EventType>(event.type)])
	{
		cb(event);
	}
}

void EventManager::Event()
{
	Publish(e);
}

EventManager& EventManager::getEventManagerInstance()
{
	static EventManager eventManager;
	return eventManager;
}