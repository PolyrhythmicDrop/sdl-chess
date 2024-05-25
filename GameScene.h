#pragma once
#include "Chessboard.h"
#include "GameManager.h"
#include "GameStateMachine.h"
#include "Player.h"
#include "Scene.h"

class IGameState;
class GameStateMachine;

class GameScene : public Scene, public IMediator
{
private:

	std::unique_ptr<Chessboard> _board;
	std::vector<Piece> _pieces;

	// Captured pieces go here.
	// Key is the color of the piece. 0 = Black, 1 = White.
	std::map<int, std::vector<Piece*>> _capturedPieces;
	// Captured white pieces are rendered here, on the top right side of the board
	SDL_Point _whiteCapturePoint;
	// Captured black pieces are rendered here, on the top right side of the board
	SDL_Point _blackCapturePoint; 

	Player _playerOne;
	Player _playerTwo;

	std::unique_ptr<GameManager> _manager;
	
	std::unique_ptr<GameStateMachine> _gsm;

	inline void setCurrentState(IGameState& state) { _currentState = &state; };
	inline void setPreviousState(IGameState& state) { _previousState = &state; };

public:
	static bool _instantiated;

	IGameState* _currentState;
	IGameState* _previousState;

	GameScene();
	~GameScene();

	inline Chessboard* getBoard() { return _board.get(); };

	void initializePieces();
	void initializeCapturePoints();

	inline Piece* getPieceOnSquare(Square* square) { return square->getOccupant(); };
	// Returns a pointer to the piece vector
	inline std::vector<Piece>* getAllPieces() { return &_pieces; };

	// Gets the index in the pieces vector of all the pieces with the specified FEN name.
	std::vector<int> getPieceIndexByFEN(char fen);
	// Returns a vector of pointers to the pieces with the specified FEN name.
	std::vector<Piece*> getPiecesByFen(char fen);

	// Gets all the captured pieces for the specified color.
	// 0 = Black, 1 = White
	std::vector<Piece*> getCapturedPieces(int color);
	// Adds the specified piece to the captured pieces map.
	void addToCapturedPieces(Piece* piece);

	inline Player* getPlayerOne() { return &_playerOne; };
	inline Player* getPlayerTwo() { return &_playerTwo; };
	inline void setPlayerOne(std::string name, char color) { _playerOne._name = name; _playerOne._color = color; };
	inline void setPlayerTwo(std::string name, char color) { _playerTwo._name = name; _playerTwo._color = color; };

	inline GameManager* getManager() { return _manager.get(); };
	void notify(GameObject* sender, std::string eString);
	void notify(GameManager* manager, std::string eString);

	inline IGameState* getCurrentState() const { return _currentState; };
	inline IGameState* getPreviousState() const { return _previousState; };
	inline void setGameState(IGameState& state) { _gsm->setGameState(this, state); };

};

