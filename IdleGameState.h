#pragma once
#include "IGameState.h"

class IdleGameState :  public IGameState
{
private:
	IdleGameState();
	IdleGameState(const IdleGameState& other);
	IdleGameState& operator=(const IdleGameState& other);

public:

	void enter(GameStateMachine* gsm);
	void changeState(GameStateMachine* gsm);
	void exit(GameStateMachine* gsm);
	static IGameState& getInstance();


	void subscribeToEventManager(EventManager& manager, GameStateMachine* gsm);
	void unsubscribeToEventManager(EventManager& manager, GameStateMachine* gsm);
};

