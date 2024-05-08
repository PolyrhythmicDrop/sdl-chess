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
	void changeState(SceneEscMenu* menuScene, std::string eventString = 0);
	void exit(SceneEscMenu* menuScene);

	static IMenuState& getInstance();

	void buildMenu(SceneEscMenu* menuScene);
	void destroyMenu(SceneEscMenu* menuScene);

	void subscribeToEventManager(EventManager& manager, SceneEscMenu* menuScene);
	void unsubscribeToEventManager(EventManager& manager, SceneEscMenu* menuScene);
};

