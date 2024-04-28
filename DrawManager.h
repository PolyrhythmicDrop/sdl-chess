#pragma once
#include <vector>
#include <map>
#include <iostream>
#include <functional>
#include <SDL.h>

class DrawManager
{
private:
	std::map<std::string, std::vector<std::function<int(SDL_Renderer*, SDL_Texture*, SDL_Rect*, SDL_Rect*)>>> _renderQueue;

public:

	void drawQueue();

};

