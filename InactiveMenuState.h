#pragma once
#include "SceneEscMenu.h"
#include "IMenuState.h"

class InactiveMenuState : public IMenuState
{
private:
	InactiveMenuState() {};
	InactiveMenuState(const InactiveMenuState& other);
	InactiveMenuState& operator=(const InactiveMenuState& other);

public:
	void enter(SceneEscMenu* menuScene);
	void changeState(SceneEscMenu* menuScene);
	void exit(SceneEscMenu* menuScene);

	static IMenuState& getInstance();
};

