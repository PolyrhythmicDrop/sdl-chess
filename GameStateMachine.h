#pragma once
#include "EventManager.h"
#include <cassert>
#include <memory>

class GameManager;
class IGameState;

class GameStateMachine
{
private:

	static bool _instantiated;

	std::shared_ptr<GameManager> _manager;

public:

	GameStateMachine(GameManager* gm);
	~GameStateMachine() {};

	inline GameManager* getGameManager() { return _manager.get(); };

	void enter(GameManager* gm);
	void changeState(GameManager* gm, std::string eventString = "");
	void exit(GameManager* gm);

	void setGameState(GameManager* gm, IGameState& newState);

	void subscribeToEventManager(EventManager& manager, GameManager* gm);
	void unsubscribeToEventManager(EventManager& manager, GameManager* gm);
};

