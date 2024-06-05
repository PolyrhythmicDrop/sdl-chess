#pragma once
#include <memory>
#include <string>
#include <vector>
#include <optional>

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
	// Format: square moved from + square moved to, i.e. "e2e4"
	std::string _fenMove = "";

	// 1. Position modifier for a FEN string
	std::string _fenPosition = "";

	// 2. Turn modifier for a FEN string.
	// 'w' = white, 'b' = black.
	char _fenColor;

	// 3. Castle modifier for a FEN string.  
	// Castling rights do not specify whether castling is actually possible, only whether or not the king has moved and the rooks have moved or been captured.
	// UP = white, low = black, K = kingside, Q = queenside. '-' = neither side has castling rights.
	std::string _fenCastle;

	std::string _fenWhiteCastle;
	std::string _whiteKingside = "K";
	std::string _whiteQueenside = "Q";

	std::string _fenBlackCastle;
	std::string _blackKingside = "k";
	std::string _blackQueenside = "q";

	// 4. Passant modifier for a FEN string. 
	// Square behind the pawn to be captured en passant, e.x. 'e3'. '-' = no passant available.
	std::string _fenPassant = "-";

	// 5. Half move clock modifier for a FEN string. 
	// How many moves both players have made since last pawn advance or piece capture. 
	// When this counter reaches 100, game should be a draw.
	int _fenHalfMove;

	// 6. Full move modifier for a FEN string.
	// The number of completed turns in a game. Should increment every time black completes a move.
	int _fenFullMove;
	

public:

	FenManager(GameManager* gm);
	~FenManager() {};

	// ** Concatenators **

	// Creates a standard FEN string, without the Stockfish-specific sections.
	std::string createFenString();
	// Creates a Stockfish-ready FEN string
	std::string createFishFen();

	// ** History Functions **

	void addToFenHistory(std::string move);
	std::vector<std::string>* getFenHistory();
	void clearFenHistory();

	// ** Set FEN Components **

	void setFenMove(std::string move);
	void setFenPosition(std::string pos);
	void setFenColor(char color);

	/// <summary>
	/// Sets the modifier for castling.
	/// </summary>
	/// <param name="castle">Whether or not castling is available</param>
	/// <param name="color">The color that can castle. 0 = black, 1 = white</param>
	/// <param name="kingside">Whether the specified color can castle kingside.</param>
	/// <param name="queenside">Whether the specified color can castle queenside.</param>
	void setCastleByColor(bool castle, int color, std::optional<bool>kingside, std::optional<bool> queenside);

	// Sets the FEN castling string by combining the _fenWhiteCastle and _fenBlackCastle strings.
	// Should be used in conjunction with setCastleByColor, which sets the castling string for each side.
	void setFenCastle();

	/// <summary>
	/// Sets the en passant modifier for the FEN string. Concatenates any passed squareName to the existing _fenPassant value.
	/// </summary>
	/// <param name="squareName">The name of the square to use as the en passant modifier. If you pass std::nullopt as the squareName, _fenPassant will reset to "-", signifying that there are no en passant moves available.</param>
	void setFenPassant(std::optional<std::string> squareName);
	// Removes a square from the FEN passant modifier. Use this once a pawn moves after its first move.
	void removeFenPassantSquare(std::string squareName);

	void plusFenHalfMove();
	void resetFenHalfMove();

	void plusFenFullMove();

};

