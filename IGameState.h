#pragma once
#include "GameStateMachine.h"

class IGameState
{
public:

	virtual ~IGameState() {};

	virtual void enter(GameStateMachine* gsm) = 0;
	virtual void changeState(GameStateMachine* gsm, std::string eventString) = 0;
	virtual void exit(GameStateMachine* gsm) = 0;

	virtual void subscribeToEventManager(EventManager& manager, GameStateMachine* gsm) = 0;
	virtual void unsubscribeToEventManager(EventManager& manager, GameStateMachine* gsm) = 0;
};

