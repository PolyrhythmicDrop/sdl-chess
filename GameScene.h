#pragma once
#include "Chessboard.h"
#include "PieceContainer.h"
#include "GameManager.h"
#include "Player.h"
#include "Scene.h"

class IGameState;
class GameStateMachine;

class GameScene : public Scene
{
private:
	friend class PieceContainer;
	friend class Player;

	std::unique_ptr<Chessboard> _board;

	PieceContainer _pieceContainer;

	// Captured white pieces are rendered here, on the top left side of the board
	SDL_Point _whiteCapturePoint;
	// Captured black pieces are rendered here, on the bottom right side of the board
	SDL_Point _blackCapturePoint; 

	Player _playerOne;
	Player _playerTwo;

	std::unique_ptr<GameManager> _manager;


public:
	static bool _instantiated;

	GameScene();
	~GameScene();

	inline Chessboard* getBoard() { return _board.get(); };
	inline PieceContainer* getPieceContainer() { return &_pieceContainer; };

	void initializeCapturePoints();
	// Adds the specified piece to the captured pieces map.
	void updateCaptureDump();

	inline Player* getPlayerOne() { return &_playerOne; };
	inline Player* getPlayerTwo() { return &_playerTwo; };
	void setPlayerOne(std::string name, int color);
	void setPlayerTwo(std::string name, int color);

	inline GameManager* getManager() { return _manager.get(); };

};

