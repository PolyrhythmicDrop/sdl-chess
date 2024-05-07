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

	// Event handler functions
	void subscribeToEventManager(EventManager& manager);

	// State functions
	inline IMenuState* getCurrentState() { return _currentState; };
	void changeState();
	void setMenuState(IMenuState& newState);

	void buildMenu();
};

