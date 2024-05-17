#pragma once

class GameScene;

class GameManager
{
private:

	GameScene* _gameScene;

public:

	GameManager(GameScene* gameScene);
	~GameManager() { };

};

