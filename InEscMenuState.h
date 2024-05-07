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
	void changeState(SceneEscMenu* menuScene, std::string eventString = 0);
	void exit(SceneEscMenu* menuScene);
	static IMenuState& getInstance();

	// Menu build and destroy functions
	void buildMenu(SceneEscMenu* menuScene);
	void destroyMenu(SceneEscMenu* menuScene);

	// Event manager functions
	void subscribeToEventManager(EventManager& manager, SceneEscMenu* menuScene);
	void unsubscribeToEventManager(EventManager& manager, SceneEscMenu* menuScene);

	void onMouseClick(SceneEscMenu* menuScene);

};

