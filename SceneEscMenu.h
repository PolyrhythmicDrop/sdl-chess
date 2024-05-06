#pragma once
#include "Scene.h"
#include "IMenuState.h"

class IMenuState;

class SceneEscMenu :  public Scene
{
private:
	IMenuState* _currentState;

public:

	SceneEscMenu();
	~SceneEscMenu();

	inline IMenuState* getCurrentState() { return _currentState; };
	void toggleState();
	void setState(IMenuState& newState);

	virtual void buildScene();
};

