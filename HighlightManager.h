#pragma once
#include "Rules.h"

class GameManager;
class Square;
class Rules;

class HighlightManager
{
private:

	friend class GameManager;

	std::shared_ptr<GameManager> _gm;

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
	void orthoHighlightOptions(Square* square, Rules::RulePackage rules, M m, T t);

	template<typename M, typename T>
	void diagHighlightOptions(Square* square, Rules::RulePackage rules, M m, T t);

	template<typename M, typename T>
	void jumpHighlightOptions(Square* square, Rules::RulePackage rules, M m, T t);

	// *********************** //

	Rules::RulePackage getPieceRules(Piece* piece);
	// Overload for getPieceRules, takes FEN notation instead of a piece object to get rules.
	Rules::RulePackage getPieceRules(char fen, bool firstMove = false);


	void highlightActionOptions(Square* square);
	void removeActionHighlight();

	// Highlight orthogonal moves
	void highlightOrthoMoveOptions(Square* square, Rules::RulePackage rules);

	// Highlight diagonal moves
	void highlightDiagMoveOptions(Square* square, Rules::RulePackage rules);

	// Highlight jump moves
	void highlightJumpMoveOptions(Square* square, Rules::RulePackage rules);

	bool highlightCheck(Square* square);

};

