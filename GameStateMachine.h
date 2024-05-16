#pragma once
#include "EventManager.h"
#include <cassert>

class GameScene;
class IGameState;


class GameStateMachine
{
private:

	static bool _instantiated;

public:

	GameStateMachine();
	~GameStateMachine() {};

	void enter(GameScene* scene);
	void changeState(GameScene* scene);
	void exit(GameScene* scene);

	void setGameState(GameScene* scene, IGameState& newState);

	void subscribeToEventManager(EventManager& manager, GameScene* scene);
	void unsubscribeToEventManager(EventManager& manager, GameScene* scene);
};

