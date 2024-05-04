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

	/// <summary>
	/// Get Rect (nerd). Returns the _dimensions of the game object, which is an SDL Rect.
	/// </summary>
	/// <returns></returns>
	virtual SDL_Rect* getDimensions();

	/// <summary>
	/// Set the width and height of the game object.
	/// </summary>
	/// <param name="w"></param>
	/// <param name="h"></param>
	virtual void setScale(int w, int h);

	/// <summary>
	/// Set the position of the game object.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	virtual void setPosition(int x, int y);

	virtual void setScaleFromTexture(SDL_Texture* texture);
};



