#pragma once
#include <iostream>

// Pure abstract class for game objects
class GameObject
{
public:
	// Keeps track of the current number of game objects.
	int static gameObjectCount;

	GameObject() 
	{ 
		gameObjectCount++;
		std::cout << "Object created! Game object count: " << gameObjectCount << "\n";
	};
	~GameObject() 
	{ 
		gameObjectCount--;
		std::cout << "Object destroyed! Game object count: " << gameObjectCount << "\n";
	};
};

