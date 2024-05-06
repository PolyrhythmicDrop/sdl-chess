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
	void changeState(SceneEscMenu* menuScene);
	void exit(SceneEscMenu* menuScene);

	static IMenuState& getInstance();

	void buildMenu(SceneEscMenu* menuScene);

};

