#pragma once
#include <windows.h>
#include <iostream>
#include <cstdio>
#include <vector>
#include <sstream>

#define BUFSIZE 4096

class Stockfish
{

private:

	HANDLE _hInRead = NULL;
	HANDLE _hInWrite = NULL;
	HANDLE _hOutRead = NULL;
	HANDLE _hOutWrite = NULL;


	STARTUPINFO _startupInfo;
	PROCESS_INFORMATION _processInfo;
	SECURITY_ATTRIBUTES _security;

	std::string fenPosition = "";

	CHAR _chBuf[BUFSIZE];

public:

	Stockfish();

	std::vector<std::string> _fishOutput;

	/// <summary>
	/// Initializes Stockfish child process and sets up input and output handles to communicate with Stockfish.
	/// </summary>
	/// <returns>True if initialization was successful, false if any step in the process failed.</returns>
	bool createStockfishProcess();

	/// <summary>
	/// Readies Stockfish to begin playing or analyzing a new game.
	/// </summary>
	/// <parameter="fen">FEN string for the starting position for this game. Defaults to the standard starting position.</parameter>
	/// <returns>True if a new game was successfully initialized, false if not.</returns>
	bool newGameStockfish(std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w -- 0 0");

	// Sends a string command to Stockfish
	void commandStockfish(std::string command);

	// Sends an "isready" command to Stockfish. Returns TRUE if Stockfish returns "readyok".
	bool isStockfishReady();

	/// <summary>
	/// Reads output from Stockfish and converts it to string.
	/// </summary>
	/// <param name="delay">The read delay. This could eventually be converted into a peek instead.</param>
	/// <returns>A vector of strings that Stockfish has outputted.</returns>
	std::vector<std::string> readStockfishOutput(DWORD delay = 500);


};

