#pragma once
#include <SDL.h>
#include "Window.h"
#include <functional>
#include <map>
#include <vector>
#include <list>
#include <string>

class EventManager
{
private:
	/// <summary>
	/// Subscriber list, in the form of a map: <string name, list of callback functions>.
	/// </summary>
	std::map< std::string, std::list<std::function<void(std::string&)>>> m_subscribers;

	std::string _eventName;
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

	/// <summary>
	/// Subscribe to the event manager and listen for a specific event.
	/// </summary>
	/// <param name="event">The event to listen for.</param>
	/// <param name="callback">The callback function to when the event is heard.</param>
	void Subscribe(const std::string event, std::function<void(std::string&)> callback);

	void Publish(std::string event);

	void Event();

};

