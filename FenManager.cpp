#include "FenManager.h"
#include "GameManager.h"

FenManager::FenManager(GameManager* gm) :
	_gm(gm),
	_history({}),
	_textAction(""),
	_textSetup("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"),
	_textPlacement(_textSetup)
{};