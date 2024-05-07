#pragma once
#include "IMenuState.h"

class InExitConfirmState :  public IMenuState
{
private:
	InExitConfirmState() {};
	InExitConfirmState(const InExitConfirmState& other);
	InExitConfirmState& operator=(const InExitConfirmState& other);

public:
	void enter(SceneEscMenu* menuScene);
	void changeState(SceneEscMenu* menuScene, std::string eventString = 0);
	void exit(SceneEscMenu* menuScene);

	static IMenuState& getInstance();

	void buildMenu(SceneEscMenu* menuScene);

	void subscribeToEventManager(EventManager& manager, SceneEscMenu* menuScene);
	void unsubscribeToEventManager(EventManager& manager, SceneEscMenu* menuScene);
};

