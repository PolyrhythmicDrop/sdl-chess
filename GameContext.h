#pragma once
#include <iostream>
#include <cassert>

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