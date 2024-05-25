#pragma once
#include "IGameState.h"
class PauseGameState : public IGameState
{
private:
	PauseGameState();
	PauseGameState(const PauseGameState& other);
	PauseGameState& operator=(const PauseGameState& other);

public:

	void enter(GameStateMachine* gsm);
	void changeState(GameStateMachine* gsm, std::string eventString = "");
	void exit(GameStateMachine* gsm);
	static IGameState& getInstance();


	void subscribeToEventManager(EventManager& manager, GameStateMachine* gsm);
	void unsubscribeToEventManager(EventManager& manager, GameStateMachine* gsm);
};

