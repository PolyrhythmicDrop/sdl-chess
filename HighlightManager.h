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

	/// <summary>
	///  Function template for the nested "for" loop that combs the BoardGrid by row and column. Use with a lambda: boardGridLoop([this](int row, int col) { your logic here });
	/// </summary>
	template<typename Func>
	void boardGridLoop(Func f);

	void getPieceRules(Square* square);

	void highlightActionOptions(Square* square);
	void removeActionHighlight();

};

