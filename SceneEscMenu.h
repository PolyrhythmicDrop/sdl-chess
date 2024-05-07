#pragma once
#include "Scene.h"

class IMenuState;

class SceneEscMenu :  public Scene
{
private:
	/// <summary>
	/// The current state of the escape menu scene. The states it can be in are:
	/// -InactiveMenuState 
	/// -InEscMenuState
	/// -InResoMenu
	/// -InExitConfirmation
	/// </summary>
	IMenuState* _currentState;
	

public:

	SceneEscMenu();
	~SceneEscMenu();

	std::map<int, GameObject*> _currentMenuObjects;

	// Event handler functions
	
	// Subscribes to a specified SDL_EventType and then calls a function (made using a lambda function) in response. Be sure to UNSUBSCRIBE from the event after you no longer need to listen for the event.
	void subscribeToEventManager(EventManager& manager);
	// Unsubscribes for the event manager. Should be called at some point after every subscribeToEventManager call, when you no longer want to "listen" for the event.
	void unsubscribeToEventManager(EventManager& manager);

	// State functions
	inline IMenuState* getCurrentState() { return _currentState; };
	void changeState();
	void setMenuState(IMenuState& newState);

	void buildMenu();
};

