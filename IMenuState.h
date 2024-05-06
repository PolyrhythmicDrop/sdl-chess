#pragma once
#include "SceneEscMenu.h"

class SceneEscMenu;

class IMenuState
{
public:
	virtual ~IMenuState() {};

	virtual void enter(SceneEscMenu* menuScene) = 0;
	virtual void changeState(SceneEscMenu* menuScene) = 0;
	virtual void exit(SceneEscMenu* menuScene) = 0;
};

