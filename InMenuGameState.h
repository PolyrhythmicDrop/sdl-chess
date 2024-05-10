#pragma once
#include "IGameState.h"

class InMenuGameState :  public IGameState
{
public:

	InMenuGameState();
	~InMenuGameState() {};

	static IGameState& getInstance();

	virtual void enter(GameStateMachine* gsm);
	virtual void changeState(GameStateMachine* gsm);
	virtual void exit(GameStateMachine* gsm);

	virtual void subscribeToEventManager(EventManager& manager, GameStateMachine* gsm);
	virtual void unsubscribeToEventManager(EventManager& manager, GameStateMachine* gsm);
};

