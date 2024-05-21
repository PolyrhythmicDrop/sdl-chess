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

	int _currentTurn; 

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
	/// Sets the mediator for every object in the GameManager's GameScene to this GameManager instance.
	/// </summary>
	void setMediators();

	/// <summary>
	/// Notify and its overloads
	/// </summary>
	/// <param name="sender"></param>
	/// <param name="eString"></param>
	void notify(GameObject* sender, std::string eString);

	// Notify overload for events that do not refer to a specific game object.
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

	void detectClickOnObject(int x, int y);
	void selectPiece(Piece* piece);

	void highlightActionOptions(Square* square);
	void removeActionHighlight();

};

