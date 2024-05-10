#pragma once
#include "IGameState.h"
class InMenuGameState :  public IGameState
{
	~InMenuGameState() {};

	virtual void enter();
	virtual void changeState();
	virtual void exit();

	virtual void subscribeToEventManager(EventManager& manager);
	virtual void unsubscribeToEventManager(EventManager& manager);
};

