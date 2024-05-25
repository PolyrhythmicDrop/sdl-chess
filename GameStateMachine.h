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

	std::shared_ptr<GameScene> _gameScene;

public:

	GameStateMachine(GameScene* scene);
	~GameStateMachine() {};

	inline GameScene* getGameScene() { return _gameScene.get(); };

	void enter(GameScene* scene);
	void changeState(GameScene* scene);
	void exit(GameScene* scene);

	void setGameState(GameScene* scene, IGameState& newState);

	void subscribeToEventManager(EventManager& manager, GameScene* scene);
	void unsubscribeToEventManager(EventManager& manager, GameScene* scene);
};

