#pragma once
#include "GameManager.h"

class GameManager;
class Square;
class Rules;

class HighlightManager
{
private:

	friend class GameManager;

	GameManager* _gm;

public:
	HighlightManager(GameManager* gm);
	~HighlightManager() {};

	// ** Function Templates ** //

	/// <summary>
	///  Function template for the nested "for" loop that combs the BoardGrid by row and column. Use with a lambda: boardGridLoop([this](int row, int col) { your logic here });
	/// </summary>
	template<typename Func>
	void boardGridLoop(Func f);

	/// <summary>
	/// Function template for move options. 
	/// Use with a lambda. moveOptions(square, rules, [](int iRow, int iCol, vectorSquares grid, intPair squareIndex)
	/// </summary>
	/// <typeparam name="Func">Required arguments for the function</typeparam>
	/// <param name="square">The square from which to highlight move options</param>
	/// <param name="rules">Rules to pass to the function</param>
	/// <param name="f">The function.</param>
	template<typename Func>
	void moveOptions(Square* square, Rules::RulePackage rules, Func f);

	template<typename F1, typename F2>
	void captureOptionLoop(Square* square, Rules::RulePackage rules, F1 f1, F2 f2);

	Rules::RulePackage getPieceRules(Piece* piece);

	void highlightActionOptions(Square* square);
	void removeActionHighlight();

	// Move highlights

	// ** ORTHOGONAL MOVES ** //
	// Highlight orthogonal moves
	void highlightOrthoMoveOptions(Square* square, Rules::RulePackage rules, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex);

	void orthoPosRowOptions(Square* square, Rules::RulePackage rules, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex);
	void orthoNegRowOptions(Square* square, Rules::RulePackage rules, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex);

	void orthoPosColOptions(Square* square, Rules::RulePackage rules, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex);
	void orthoNegColOptions(Square* square, Rules::RulePackage rules, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex);

	// Capture highlights

	// Highlight orthogonal captures
	void highlightOrthoCaptureOptions(Square* square, Rules::RulePackage rules);
	// Highlight diagonal captures
	void highlightDiagCaptureOptions(Square* square, Rules::RulePackage rules);
};

