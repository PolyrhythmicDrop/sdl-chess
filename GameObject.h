#pragma once
#include <iostream>
#include <SDL.h>

// Pure abstract class for game objects
class GameObject
{
protected:
	std::string _name;
	// Structure of dimensions for game objects
	struct dim {
		int x, y;
		int w, h;				
	}_dimensions;
	

public:
	// Keeps track of the current number of game objects.
	int static gameObjectCount;
	
	GameObject(std::string name);
	
	~GameObject();

	std::string virtual getName();

	dim virtual getDimensions();
};



