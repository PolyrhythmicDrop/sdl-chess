#pragma once
#include "IdleProgramState.h"
#include "SceneEscMenu.h"
#include <cassert>

class IProgramState;

class ProgramStateMachine
{
private:

	IProgramState* _currentState;
	IProgramState* _previousState;

	static bool _instantiated;

	SceneEscMenu* _escMenu;

public:

	ProgramStateMachine();
	~ProgramStateMachine() {};

	// State functions
	void changeState();
	void setProgramState(IProgramState& newState);
	inline IProgramState* getCurrentState() { return _currentState; };
	inline IProgramState* getPreviousState() { return _previousState; };

	// Subscribes to a specified SDL_EventType and then calls a function (made using a lambda function) in response. Be sure to UNSUBSCRIBE from the event after you no longer need to listen for the event.
	void subscribeToEventManager(EventManager& manager);
	// Unsubscribes for the event manager. Should be called at some point after every subscribeToEventManager call, when you no longer want to "listen" for the event.
	void unsubscribeToEventManager(EventManager& manager);

	inline SceneEscMenu* getEscMenu() { return _escMenu; };
	inline void createEscMenu() { _escMenu = new SceneEscMenu; };

	

	

};

