#pragma once
#include "Chessboard.h"
#include "GameManager.h"
#include "GameStateMachine.h"
#include "Player.h"
#include "Scene.h"

class IGameState;
class GameStateMachine;

class GameScene : public Scene
{
private:

	std::unique_ptr<Chessboard> _board;
	std::vector<Piece> _pieces;
	Player _playerOne;
	Player _playerTwo;

	std::unique_ptr<GameManager> _manager;
	
	GameStateMachine* _gsm;

public:
	static bool _instantiated;

	IGameState* _currentState;
	IGameState* _previousState;

	GameScene();
	~GameScene();

	inline Chessboard* getBoard() { return _board.get(); };

	void initializePieces();

	inline Piece* getPieceOnSquare(Square* square) { return square->getOccupant(); };
	// Returns a pointer to the piece vector
	inline std::vector<Piece>* getAllPieces() { return &_pieces; };
	std::vector<int> getPiecesByFEN(char fen);

	inline Player* getPlayerOne() { return &_playerOne; };
	inline Player* getPlayerTwo() { return &_playerTwo; };
	inline void setPlayerOne(std::string name, char color) { _playerOne._name = name; _playerOne._color = color; };
	inline void setPlayerTwo(std::string name, char color) { _playerTwo._name = name; _playerTwo._color = color; };

	inline GameManager* getManager() { return _manager.get(); };

	inline IGameState* getCurrentState() const { return _currentState; };
	inline IGameState* getPreviousState() const { return _previousState; };
	inline void setCurrentState(IGameState& state) { _currentState = &state; };
	inline void setPreviousState(IGameState& state) { _previousState = &state; };
	inline void setGameState(IGameState& state) { _gsm->setGameState(this, state); };


};

