#pragma once
#include "IGameState.h"
#include "GameStateMachine.h"

class InMenuGameState :  public IGameState
{
public:

	InMenuGameState();
	~InMenuGameState() {};

	static IGameState& getInstance();

	virtual void enter(GameStateMachine* gsm);
	virtual void changeState(GameStateMachine* gsm, std::string eventString);
	virtual void exit(GameStateMachine* gsm);

	virtual void subscribeToEventManager(EventManager& manager, GameStateMachine* gsm);
	virtual void unsubscribeToEventManager(EventManager& manager, GameStateMachine* gsm);
};

