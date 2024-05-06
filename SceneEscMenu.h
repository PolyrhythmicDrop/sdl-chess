#pragma once
#include "Scene.h"
#include "IMenuState.h"

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

	InputComponent* _input;

public:

	SceneEscMenu(InputComponent* input);
	~SceneEscMenu();

	inline IMenuState* getCurrentState() { return _currentState; };
	void changeState();
	void setMenuState(IMenuState& newState);

	InputComponent* getInputComponent();

	void buildMenu();
};

