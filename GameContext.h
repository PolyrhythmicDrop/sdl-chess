#pragma once
#include "GameObject.h"
#include "Square.h"
#include <cassert>
#include <vector>

	class GameContext
	{
	private:

		static bool _instantiated;		

	public:

		std::vector<GameObject*> _gameObjects;

		// Constructor
		GameContext();

		// Deconstructor
		~GameContext();

	};