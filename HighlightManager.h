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

	template<typename M, typename T>
	void diagMoveOptions(Square* square, Rules::RulePackage rules, M m, T t);

	template<typename F1, typename F2>
	void captureOptionLoop(Square* square, Rules::RulePackage rules, F1 f1, F2 f2);

	// *********************** //

	Rules::RulePackage getPieceRules(Piece* piece);

	void highlightActionOptions(Square* square);
	void removeActionHighlight();

	// ** MOVE HIGHLIGHTS ** //

	// ** ORTHOGONAL MOVES ** //
	// Highlight orthogonal moves
	void highlightOrthoMoveOptions(Square* square, Rules::RulePackage rules, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex);

	void orthoMovePosRowOptions(Square* square, Rules::RulePackage rules, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex);
	void orthoMoveNegRowOptions(Square* square, Rules::RulePackage rules, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex);

	void orthoMovePosColOptions(Square* square, Rules::RulePackage rules, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex);
	void orthoMoveNegColOptions(Square* square, Rules::RulePackage rules, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex);

	// ** DIAGONAL MOVES ** //
	// Highlight diagonal moves
	void highlightDiagMoveOptions(Square* square, Rules::RulePackage rules);

	void diagMovePosRowOptions(Square* square, Rules::RulePackage rules, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex);
	void diagMoveNegRowOptions(Square* square, Rules::RulePackage rules, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex);

	void diagMovePosColOptions(Square* square, Rules::RulePackage rules, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex);
	void diagMoveNegColOptions(Square* square, Rules::RulePackage rules, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex);


	// ********************** //
	
	// ** CAPTURE HIGHLIGHTS ** //

	// ** ORTHOGONAL CAPTURES ** //
	// Highlight orthogonal captures
	void highlightOrthoCaptureOptions(Square* square, Rules::RulePackage rules, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex);

	void orthoCapturePosRowOptions(Square* square, Rules::RulePackage rules, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex);
	void orthoCaptureNegRowOptions(Square* square, Rules::RulePackage rules, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex);

	void orthoCapturePosColOptions(Square* square, Rules::RulePackage rules, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex);
	void orthoCaptureNegColOptions(Square* square, Rules::RulePackage rules, std::vector<std::vector<Square>>* grid, std::pair<int, int> squareIndex);
	
	// **************************


	// Highlight diagonal captures
	void highlightDiagCaptureOptions(Square* square, Rules::RulePackage rules);
};

