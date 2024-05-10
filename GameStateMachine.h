#pragma once
#include "IdleGameState.h"
#include "SceneEscMenu.h"
#include <cassert>

class IGameState;

class GameStateMachine
{
private:

	IGameState* _currentState;
	IGameState* _previousState;

	static bool _instantiated;

	SceneEscMenu* _escMenu;

public:

	GameStateMachine();
	~GameStateMachine() {};

	// State functions
	void changeState();
	void setGameState(IGameState& newState);
	inline IGameState* getCurrentState() { return _currentState; };
	inline IGameState* getPreviousState() { return _previousState; };

	// Subscribes to a specified SDL_EventType and then calls a function (made using a lambda function) in response. Be sure to UNSUBSCRIBE from the event after you no longer need to listen for the event.
	void subscribeToEventManager(EventManager& manager);
	// Unsubscribes for the event manager. Should be called at some point after every subscribeToEventManager call, when you no longer want to "listen" for the event.
	void unsubscribeToEventManager(EventManager& manager);

	inline SceneEscMenu* getEscMenu() { return _escMenu; };
	inline void createEscMenu() { _escMenu = new SceneEscMenu; };

	

	

};

