#pragma once
#include "IMenuState.h"

class InResoMenuState :  public IMenuState
{
private:
	InResoMenuState() {};
	InResoMenuState(const InResoMenuState& other);
	InResoMenuState& operator=(const InResoMenuState& other);

public:
	void enter(SceneEscMenu* menuScene);
	void changeState(SceneEscMenu* menuScene, std::string eventString = 0);
	void exit(SceneEscMenu* menuScene);

	static IMenuState& getInstance();

	void buildMenu(SceneEscMenu* menuScene);

	void subscribeToEventManager(EventManager& manager, SceneEscMenu* menuScene);

};

