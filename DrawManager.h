#pragma once
#include <vector>
#include <map>
#include <iostream>
#include <functional>
#include <SDL.h>
#include "Renderer.h"

class DrawManager
{
private:
	const Renderer* _renderer;

public:

	DrawManager(Renderer* renderer);

	~DrawManager();

	void drawQueue();

};

