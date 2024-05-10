#pragma once
#include "IGameState.h"
class IdleGameState :  public IGameState
{
	virtual ~IdleGameState() {};

	virtual void enter();
	virtual void changeState();
	virtual void exit();

	virtual void subscribeToEventManager(EventManager& manager);
	virtual void unsubscribeToEventManager(EventManager& manager);
};

