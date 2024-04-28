
#include "GameContext.h"

GameContext::GameData::GameData() { std::cout << "Game context initialized!"; };
GameContext::GameData::~GameData() { std::cout << "Game context deconstructed"; };

void GameContext::GameData::InitializeGameContext(Window window, Renderer renderer)
{
	_window = window;
	_renderer = renderer;
}
