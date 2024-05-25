#pragma once
#include "IGameState.h"
#include "GameScene.h"

class TurnBlackGameState : public IGameState
{
private:
	TurnBlackGameState();
	TurnBlackGameState(const TurnBlackGameState& other);
	TurnBlackGameState& operator=(const TurnBlackGameState& other);

public:

	void enter(GameStateMachine* gsm);
	void changeState(GameStateMachine* gsm);
	void exit(GameStateMachine* gsm);
	static IGameState& getInstance();


	void subscribeToEventManager(EventManager& manager, GameStateMachine* gsm);
	void unsubscribeToEventManager(EventManager& manager, GameStateMachine* gsm);
};

