#pragma once
#include "IMenuState.h"
#include "SceneEscMenu.h"

class InEscMenuState : public IMenuState
{
private:
	InEscMenuState() {};
	InEscMenuState(const InEscMenuState& other);
	InEscMenuState& operator=(const InEscMenuState& other);

public:

	// State machine functions
	void enter(SceneEscMenu* menuScene);
	void changeState(SceneEscMenu* menuScene);
	void exit(SceneEscMenu* menuScene);
	static IMenuState& getInstance();

	// State-specific functions
	void buildMenu(SceneEscMenu* menuScene);

};

