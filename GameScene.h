#pragma once
#include "Scene.h"
#include "Chessboard.h"
#include "Rules.h"
#include "GameManager.h"
#include "GameStateMachine.h"
#include "Player.h"
#include <memory>

class IGameState;
class GameStateMachine;

class GameScene : public Scene
{
private:

	std::unique_ptr<Chessboard> _board;
	std::vector<Piece*> _pieces;
	Player* _playerOne;
	Player* _playerTwo;

	std::unique_ptr<Rules> _rules;
	std::unique_ptr<GameManager> _manager;
	
	GameStateMachine* _gsm;

public:
	IGameState* _currentState;
	IGameState* _previousState;

	GameScene();
	~GameScene() {};

	inline Chessboard* getBoard() { return _board.get(); };
	inline std::vector<Piece*> getPieces() { return _pieces; };
	inline Player* getPlayerOne() { return _playerOne; };
	inline Player* getPlayerTwo() { return _playerTwo; };

	inline Rules* getRules() { return _rules.get(); };
	inline GameManager* getManager() { return _manager.get(); };

	inline IGameState* getCurrentState() const { return _currentState; };
	inline IGameState* getPreviousState() const { return _previousState; };
	inline void setCurrentState(IGameState& state) { _currentState = &state; };
	inline void setPreviousState(IGameState& state) { _previousState = &state; };
	inline void changeState() { _gsm->changeState(this); };


};

