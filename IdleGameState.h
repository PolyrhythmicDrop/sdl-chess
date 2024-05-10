#pragma once
#include "IGameState.h"

class IdleGameState :  public IGameState
{
public:

	IdleGameState();
	~IdleGameState() {};

	static IGameState& getInstance();

	virtual void enter(GameStateMachine* gsm);
	virtual void changeState(GameStateMachine* gsm, std::string eventString);
	virtual void exit(GameStateMachine* gsm);

	virtual void subscribeToEventManager(EventManager& manager, GameStateMachine* gsm);
	virtual void unsubscribeToEventManager(EventManager& manager, GameStateMachine* gsm);
};

