#pragma once
#include <iostream>
#include "EventManager.h"
#include "IMediator.h"

// Pure abstract class for game objects
class GameObject
{

public:

	GameObject(std::string name = "", IMediator* mediator = nullptr);

	~GameObject();

	/// <summary>
	/// Sets the mediator for this object
	/// </summary>
	/// <param name="mediator">The mediator for this object</param>
	virtual void setMediator(IMediator* mediator);

	virtual const std::string& getName() const;
	virtual void setName(const std::string& name);

	/// <summary>
	/// Get Rect (nerd). Returns the _dimensions of the game object, which is an SDL Rect.
	/// </summary>
	/// <returns></returns>
	virtual const SDL_Rect* getDimensions() const;

	/// <summary>
	/// Set the width and height of the game object.
	/// </summary>
	/// <param name="w"></param>
	/// <param name="h"></param>
	virtual void setScale(int w, int h);

	virtual int getWidth() const;

	virtual int getHeight() const;

	/// <summary>
	/// Set the position of the game object.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	virtual void setPosition(int x, int y);
	virtual inline int getX() { return _dimensions.x; };
	virtual inline int getY() { return _dimensions.y; };

	virtual void setScaleFromTexture(SDL_Texture* texture);

protected:

	IMediator* _mediator;

	// Name of the game object
	std::string _name;

	// Dimensions for game objects
	SDL_Rect _dimensions;

	// Keeps track of the current number of game objects.
	int static gameObjectCount;
};



