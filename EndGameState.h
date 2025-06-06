#pragma once
#include "IGameState.h"
#include "GameScene.h"

class EndGameState :  public IGameState
{
private:
	EndGameState();
	EndGameState(const EndGameState& other);
	EndGameState& operator=(const EndGameState& other);

public:

	void enter(GameStateMachine* gsm);
	void changeState(GameStateMachine* gsm, std::string eventString = "");
	void exit(GameStateMachine* gsm);
	static IGameState& getInstance();


	void subscribeToEventManager(EventManager& manager, GameStateMachine* gsm);
	void unsubscribeToEventManager(EventManager& manager, GameStateMachine* gsm);
};

