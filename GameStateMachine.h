#pragma once
#include "EventManager.h"
#include <cassert>
#include <memory>

class GameScene;
class IGameState;


class GameStateMachine
{
private:

	static bool _instantiated;

	GameScene* _gameScene;

public:
	

	GameStateMachine();
	~GameStateMachine() {};

	inline void setGameScene(GameScene* scene) { _gameScene = scene; };
	inline GameScene* getGameScene() { return _gameScene; };

	void enter(GameScene* scene);
	void changeState(GameScene* scene);
	void exit(GameScene* scene);

	void setGameState(GameScene* scene, IGameState& newState);

	void subscribeToEventManager(EventManager& manager, GameScene* scene);
	void unsubscribeToEventManager(EventManager& manager, GameScene* scene);
};

