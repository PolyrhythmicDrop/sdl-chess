#pragma once
#include "IMenuState.h"
#include "SceneEscMenu.h"

class InEscMenu : public IMenuState
{
private:
	InEscMenu() {};
	InEscMenu(const InEscMenu& other);
	InEscMenu& operator=(const InEscMenu& other);

public:
	void enter(SceneEscMenu* menuScene);
	void changeState(SceneEscMenu* menuScene);
	void exit(SceneEscMenu* menuScene);

	static IMenuState& getInstance();

};

