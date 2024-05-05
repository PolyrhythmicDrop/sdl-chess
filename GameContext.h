#pragma once
#include <cassert>
#include <iostream>
#include <vector>

	class GameContext
	{
	private:

		static bool _instantiated;		

	public:

		// Keeps track of the current number of game objects.
		int static gameObjectCount;

		// Constructor
		GameContext();

		// Deconstructor
		~GameContext();

	};