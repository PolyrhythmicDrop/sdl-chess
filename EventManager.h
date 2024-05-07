#pragma once
#include "SDLfunc.h"
#include <functional>
#include <map>

class EventManager
{
public: 
	using eventCallback = std::function<void(SDL_Event const&)>;

	SDL_Event e;

	/// <summary>
	/// Default constructor for the Event Manager
	/// </summary>
	EventManager();

	/// <summary>
	/// Polls the SDL event queue for events, then calls the Event Manager's Event() function.
	/// </summary>
	/// <param name="e">The event variable to use in the event queue</param>
	/// <param name="quit">Flag to quit the whole program and the event loop.</param>
	void HandleEvents(bool* quit);

	/// <summary>
	/// Subscribe to the event manager and listen for a specific event.
	/// </summary>
	/// <param name="type">The event type to listen for.</param>
	/// <param name="callback">The callback function to use when the event is heard.</param>
	void Subscribe(SDL_EventType type, eventCallback callback);

	/// <summary>
	/// Publishes the event for consumption.
	/// </summary>
	/// <param name="event"></param>
	void Publish(SDL_Event event);

	void Event();

	static EventManager& getEventManagerInstance();

private:
	/// <summary>
	/// Subscriber list, in the form of a map: <SDL_EventType, list of callback functions (eventCallback)>.
	/// </summary>
	std::map< SDL_EventType, std::vector<eventCallback>> _subscribedCallbacks;
};

