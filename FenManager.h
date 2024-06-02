#pragma once
#include <memory>
#include <vector>
#include <string>

class GameManager;

class FenManager
{
	friend class GameManager;

private:

	std::shared_ptr<GameManager> _gm;

	// Record of past moves, as strings
	std::vector<std::string> _history;
	// A text version of an action, in long algebraic notation for UCI. Should be able to be parsed by Stockfish and SDL Chess, to be used in the history list and for Stockfish move calculation
	std::string _textAction;
	// Stringified version of game setup. Should be in UCI-readable format, using FEN. Hard-coded to start with, but in later versions of SDL Chess I'd like to let users put in their own starting positions
	std::string _textSetup;
	// The current placement of all the pieces on the board. FEN: first field
	std::string _textPlacement;

public:

	FenManager(GameManager* gm);
	~FenManager() {};

};

