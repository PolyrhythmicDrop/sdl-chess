#pragma once
#include "ActionManager.h"
#include "IMediator.h"
#include "Rules.h"
#include "SelectionManager.h"
#include "HighlightManager.h"
#include "FenManager.h"
#include "GameStateMachine.h"
#include "FishManager.h"
#include <memory>
#include <vector>


class GameScene;
class Square;
class HighlightManager;
class ActionManager;
class SelectionManager;
class FenManager;
class FishManager;
class Player;

class GameManager : public IMediator
{
	friend class HighlightManager;
	friend class ActionManager;
	friend class SelectionManager;
	friend class FenManager;
	friend class FishManager;

private:

	GameScene* _gameScene;

	// The current turn. 0 = Black, 1 = White.
	int _currentTurn;

	// The player whose turn it currently is.
	Player* _currentPlayer;
	Player* _previousPlayer;

	// The winner of the game. Set after checkmate.
	Player* _victor = nullptr;

	// Whether or not the game being played is against the AI. True if against AI, false if human to human game.
	bool _aiMode;

	// The currently selected piece
	Piece* _selectedPiece;

	enum VictoryCondition {
		CHECKMATE,
		DRAW,
		NONE
	};

	VictoryCondition _victory = VictoryCondition::NONE;

	std::unique_ptr<Rules> _rules;

	std::unique_ptr<GameStateMachine> _gsm;

	// ** Manager Components ** //
	// ************************ //

	std::unique_ptr<FishManager> _fishManager;
	std::unique_ptr<HighlightManager> _highlightManager;
	std::unique_ptr<ActionManager> _actionManager;
	std::unique_ptr<SelectionManager> _selectionManager;
	std::unique_ptr<FenManager> _fenManager;

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

	// Game object notifications
	void notify(GameObject* sender, std::string eString);

	// Notify overload for events that do not come from a specific game object.
	void notify(std::string eString);

	// *******************************

	// ** Game Initialization Functions **


	void setUpGame();
	bool setGameMode();
	void setUpPlayers();
	// Takes a FEN string and translates it to a board layout
	void fenToBoard(std::string position);
	// Takes a board layout and translates it to a FEN string for use with Stockfish
	std::string boardToFen();
	void setUpBoard();

	// Takes a custom FEN, sets the FEN Manager's position using it, and returns the same string. Default is default starting position.
	std::string setUpScenario(std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

	// Sets pieces on the board in the default starting position. 
	// Consider folding this into fenToBoard, or renaming fenToBoard to setUpPieces() to allow for different starting positions.
	void setUpPieces();
	// Initialize the Stockfish chess engine for use as an AI player or to deduce checkmate
	void setUpStockfish();

	// *****************************

	inline Rules* getRules() { return _rules.get(); };
	inline Player* getCurrentPlayer() { return _currentPlayer; };
	inline VictoryCondition* getVictoryCondition() { return &_victory; };
	inline Player* getVictor() { return _victor; };

	// Sets what turn it is. True/1 = white, False/0 = black.
	void setTurn(bool color);
	inline int getTurn() const { return _currentTurn; };

	// Checks for check on the current player's king.
	bool checkForCheck();
	bool checkForCheckmate();

	// Check if castling is available
	void checkForCastle(Piece* piece);

	// **********************

	// ** Handler Functions **

	void handleClick();

	void onPieceMove(Piece* piece);
	void onPieceCapture(Piece* piece);
	void onPieceRevive(Piece* piece);
	void onTurnStart();

	// Disables en passant capturing for any pawns that moved two squares up on the previous turn.
	void endPassant();

	void fenTurnEnd();
	// Perform end-of-turn actions and change the state to the next turn.
	void endTurn();

	void FenPassantChange(Piece* piece);
	void onStockfishTurn();
	void executeFishMove();

	// Handles end of turn FEN string creation and concatenation.
	void setCurrentFen();

	void onCheckmate();

};

