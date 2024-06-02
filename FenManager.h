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

	// Record of past FEN strings
	std::vector<std::string> _history;

	// Total concatenated FEN notation line
	std::string _fenString = "";
	// Move modifier for a FEN string. Used only for Stockfish
	std::string _fenMove = "";

	// 1. Position modifier for a FEN string
	std::string _fenPosition = "";

	// 2. Turn modifier for a FEN string.
	// 'w' = white, 'b' = black.
	char _fenColor;

	// 3. Castle modifier for a FEN string.
	// UP = white, low = black, K = kingside, Q = queenside. '-' = neither side can castle
	std::string _fenCastle = "";

	// 4. Passant modifier for a FEN string. 
	// Square behind the pawn to be captured en passant, e.x. 'e3'. '-' = no passant available.
	std::string _fenPassant = "";

	// 5. Half move clock modifier for a FEN string. 
	// How many moves both players have made since last pawn advance or piece capture. 
	// When this counter reaches 100, game should be a draw.
	char _fenHalfMove;

	// 6. Full move modifier for a FEN string.
	// The number of completed turns in a game. Should increment every time black completes a move.
	char _fenFullMove;
	

public:

	FenManager(GameManager* gm);
	~FenManager() {};

	std::string createFenString();
	// Creates a Stockfish-ready FEN string
	std::string createFishFen();

	void addToFenHistory(std::string move);
	std::vector<std::string>* getFenHistory();
	void clearFenHistory();

	void setFenMove(std::string move);
	void setFenPosition(std::string pos);
	void setFenColor(char color);

	/// <summary>
	/// Sets the modifier for castling.
	/// </summary>
	/// <parameter="castle">Whether or not castling is available</parameter>
	/// <parameter="color">The color that can castle. 0 = black, 1 = white</parameter>
	std::string setCastleByColor(bool castle, int color, bool kingside, bool queenside);
	void setFenCastle(std::string white, std::string black);

	void setFenPassant(std::string squareName);
	void plusFenHalfMove();
	void plusFenFullMove();

};

