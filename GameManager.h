#pragma once
#include "ActionManager.h"
#include "IMediator.h"
#include "Rules.h"
#include "SelectionManager.h"
#include "HighlightManager.h"
#include "GameStateMachine.h"
#include "Stockfish.h"
#include <memory>
#include <vector>


class GameScene;
class Square;
class HighlightManager;
class ActionManager;
class SelectionManager;
class Player;

class GameManager : public IMediator
{
	friend class HighlightManager;
	friend class ActionManager;
	friend class SelectionManager;

private:

	GameScene* _gameScene;

	// The current turn. 0 = Black, 1 = White.
	int _currentTurn; 

	// The player whose turn it currently is.
	Player* _currentPlayer;

	// Whether or not the game being played is against the AI. True if against AI, false if human to human game.
	bool _aiMode;

	// The currently selected piece
	Piece* _selectedPiece;

	// ** FEN/Stockfish Strings ** //
	// *************************** //
	
	// Record of past moves, as strings
	std::vector<std::string> _history;
	// A text version of an action, in long algebraic notation for UCI. Should be able to be parsed by Stockfish and SDL Chess, to be used in the history list and for Stockfish move calculation
	std::string _textAction;
	// Stringified version of game setup. Should be in UCI-readable format, using FEN. Hard-coded to start with, but in later versions of SDL Chess I'd like to let users put in their own starting positions
	std::string _textSetup;
	// The current placement of all the pieces on the board. FEN: first field
	std::string _textPlacement;

	// ** Manager Components ** //
	// ************************ //
	
	std::unique_ptr<Rules> _rules;
	std::unique_ptr<GameStateMachine> _gsm;
	std::unique_ptr<HighlightManager> _highlightManager;
	std::unique_ptr<ActionManager> _actionManager;
	std::unique_ptr<SelectionManager> _selectionManager;
	std::unique_ptr<Stockfish> _stockfish;

	// *****************************

	// Private State Machine Functions
	inline void setCurrentState(IGameState& state) { _currentState = &state; };
	inline void setPreviousState(IGameState& state) { _previousState = &state; };


public:

	IGameState* _currentState;
	IGameState* _previousState;

	GameManager(GameScene* gameScene);
	~GameManager() { };

	// ** Function Templates ** //

	/// <summary>
	///  Function template for the nested "for" loop that combs the BoardGrid by row and column. Use with a lambda: boardGridLoop([this](int row, int col) { your logic here });
	/// </summary>
	template<typename Func>
	void boardGridLoop(Func f);

	// ********************************

	// ** State Machine Functions ** //
	inline IGameState* getCurrentState() const { return _currentState; };
	inline IGameState* getPreviousState() const { return _previousState; };
	inline void setGameState(IGameState& state) { _gsm->setGameState(this, state); };
	
	// ********************************

	// ** Mediator Functions **

	/// <summary>
	/// Sets the mediator for every object in the GameManager's GameScene to this GameManager instance.
	/// </summary>
	void setMediators();

	/// <summary>
	/// Game object notifications
	/// </summary>
	/// <param name="sender"></param>
	/// <param name="eString"></param>
	void notify(GameObject* sender, std::string eString);

	// Notify overload for events that do not come from a specific game object.
	void notify(std::string eString);

	// *******************************

	// ** Game Initialization Functions **

	void parseFEN(std::string position);
	void setUpGame();
	bool setGameMode();
	void setUpPlayers();
	void setUpBoard();
	void setUpPieces();
	// If using Stockfish chess engine, initialize it for Player Two, the AI player.
	void setUpStockfish();
	

	// *****************************

	// ** Getters and Setters **

	inline Rules* getRules() { return _rules.get(); };
	inline Player* getCurrentPlayer() { return _currentPlayer; };

	// *************************

	// ** Turn Functions **

	void setTurn(int turn);
	inline int getTurn() const { return _currentTurn; };

	// Checks for check on the current player's king.
	bool checkForCheck();

	void checkForCastle(Piece* piece);

	// Notifies the game state machine to change the turn.
	void endTurn();
	// Disables en passant capturing for any pawns that moved two squares up on the previous turn.
	void endPassant();

	// **********************

	// Handler functions
	// ***********************

	void handleClick();
	void onPieceMove(Piece* piece);
	void onTurnChange();

};

