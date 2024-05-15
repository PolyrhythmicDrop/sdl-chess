#pragma once
#include <iostream>
#include "SDLfunc.h"

#include "EventManager.h"

// Pure abstract class for game objects
class GameObject
{
protected:
	std::string _name;
	// Structure of dimensions for game objects
	SDL_Rect _dimensions;
	// Z-index for drawing purposes. Higher values render on top of lower values.
	int _zIndex;

	// Keeps track of the current number of game objects.
	int static gameObjectCount;


public:

	GameObject(std::string name = "");

	~GameObject();

	bool _draw;

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

	virtual int getWidth();

	virtual int getHeight();

	int getZ();

	/// <summary>
	/// Sets the Z-value for this object.
	/// </summary>
	/// <param name="z"></param>
	void setZ(int z);

	/// <summary>
	/// Set the position of the game object.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	virtual void setPosition(int x, int y);
	virtual inline int getX() { return _dimensions.x; };
	virtual inline int getY() { return _dimensions.y; };

	virtual void setScaleFromTexture(SDL_Texture* texture);
};



