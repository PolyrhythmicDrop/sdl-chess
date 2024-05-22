#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include "Rules.h"
#include "IMediator.h"

class GameScene;
class Square;

class GameManager : public IMediator
{
private:

	GameScene* _gameScene;
	std::unique_ptr<Rules> _rules;

	// The current turn. 0 = Black, 1 = White.
	int _currentTurn; 

	Piece* _selectedPiece;

	// Record of past moves, as strings
	std::vector<std::string> _history;

	// ** FEN/Stockfish Strings ** //
	
	// A text version of an action, in long algebraic notation for UCI. Should be able to be parsed by Stockfish and SDL Chess, to be used in the history list and for Stockfish move calculation
	std::string _textAction;
	// Stringified version of game setup. Should be in UCI-readable format, using FEN. Hard-coded to start with, but in later versions of SDL Chess I'd like to let users put in their own starting positions
	std::string _textSetup;
	// The current placement of all the pieces on the board. FEN: first field
	std::string _textPlacement;

	// *******************************


public:

	GameManager(GameScene* gameScene);
	~GameManager() { };

	/// <summary>
	///  Function template for the nested "for" loop that combs the BoardGrid by row and column. Use with a lambda: boardGridLoop([this](int row, int col) { your logic here });
	/// </summary>
	template<typename Func>
	void boardGridLoop(Func f);


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

	inline Rules* getRules() { return _rules.get(); };

	// Game setup functions
	// *********************

	void parseFEN(std::string position);
	void setUpGame();

	// Turn-specific functions
	// ***********************

	void setTurn(int turn);
	inline int getTurn() const { return _currentTurn; };

	// Handle Click Functions
	// ***********************

	/// <summary>
	/// Handles a click on a square and calls different functions, depending on what was clicked and in what context.
	/// </summary>
	void handleClickOnBoard(int x, int y);

	void handleClickOnEmptySquare(Square* square);

	void handleClickOnPiece(Piece* piece);

	// Piece and action highlighting
	// ***********************

	/// <summary>
	/// Selects a specific piece.
	/// </summary>
	/// <param name="piece">The piece to select.</param>
	void selectPiece(Piece* piece);

	/// <summary>
	/// Deselects all selected pieces on the board.
	/// </summary>
	/// <param name="exception">Deselects all pieces but this one. Optional field.</param>
	void deselectPieces(Piece* exception = nullptr);

	void highlightActionOptions(Square* square);
	void removeActionHighlight();

	// Move and Capture Functions
	// ***************************

	/// <summary>
	/// Moves a piece to the target square.
	/// </summary>
	/// <param name="piece">The piece to move.</param>
	/// <param name="target">The square to move to.</param>
	void movePiece(Piece* piece, Square* target);

	/// <summary>
	/// Captures the specified piece.
	/// </summary>
	/// <param name="attacker">The piece that is capturing.</param>
	/// <param name="defender">The piece to be captured.</param>
	void capturePiece(Piece* attacker, Piece* defender);

};

