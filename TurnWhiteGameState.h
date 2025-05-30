#pragma once
#include "IGameState.h"
#include "GameScene.h"

class TurnWhiteGameState : public IGameState
{
private:
	TurnWhiteGameState();
	TurnWhiteGameState(const TurnWhiteGameState& other);
	TurnWhiteGameState& operator=(const TurnWhiteGameState& other);

public:

	void enter(GameStateMachine* gsm);
	void changeState(GameStateMachine* gsm, std::string eventString);
	void exit(GameStateMachine* gsm);
	static IGameState& getInstance();

	void subscribeToEventManager(EventManager& manager, GameStateMachine* gsm);
	void unsubscribeToEventManager(EventManager& manager, GameStateMachine* gsm);

};

