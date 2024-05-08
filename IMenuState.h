#pragma once
#include "SceneEscMenu.h"

class SceneEscMenu;

class IMenuState
{
public:
	virtual ~IMenuState() {};

	virtual void enter(SceneEscMenu* menuScene) = 0;
	virtual void changeState(SceneEscMenu* menuScene, std::string eventString = 0) = 0;
	virtual void exit(SceneEscMenu* menuScene) = 0;

	virtual void buildMenu(SceneEscMenu* menuScene) = 0;
	virtual void destroyMenu(SceneEscMenu* menuScene) = 0;

	virtual void subscribeToEventManager(EventManager& manager, SceneEscMenu* menuScene) = 0;
	virtual void unsubscribeToEventManager(EventManager& manager, SceneEscMenu* menuScene) = 0;
};

