#pragma once
#include "IGameState.h"

class InitGameState : public IGameState
{
private:
	InitGameState();
	InitGameState(const InitGameState& other);
	InitGameState& operator=(const InitGameState& other);

public:

	void enter(GameStateMachine* gsm);
	void changeState(GameStateMachine* gsm);
	void exit(GameStateMachine* gsm);
	static IGameState& getInstance();


	void subscribeToEventManager(EventManager& manager, GameStateMachine* gsm);
	void unsubscribeToEventManager(EventManager& manager, GameStateMachine* gsm);
};

