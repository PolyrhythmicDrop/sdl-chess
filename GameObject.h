#pragma once
#include <iostream>
#include <SDL.h>

// Pure abstract class for game objects
class GameObject
{
protected:
	std::string _name;
	// Structure of dimensions for game objects
	SDL_Rect _dimensions;
	

public:
	// Keeps track of the current number of game objects.
	int static gameObjectCount;
	
	GameObject(std::string name = "");
	
	~GameObject();

	virtual std::string getName();

	virtual SDL_Rect* getDimensions();

	virtual void setDimensions(int x, int y, int w, int h);

	virtual void setDimensionsFromTexture(SDL_Texture* texture);
};



