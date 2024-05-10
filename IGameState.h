#pragma once
#include "EventManager.h"

class IGameState
{
public:
	virtual ~IGameState() {};

	virtual void enter() = 0;
	virtual void changeState() = 0;
	virtual void exit() = 0;

	virtual void subscribeToEventManager(EventManager& manager) = 0;
	virtual void unsubscribeToEventManager(EventManager& manager) = 0;
};

