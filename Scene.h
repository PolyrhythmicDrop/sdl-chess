#pragma once
#include "GameObject.h"
#include "IDrawable.h"
#include <map>

/// <summary>
/// Abstract class for building scenes.
/// </summary>
class Scene
{
protected:

	/// <summary>
	/// Vector containing all the objects in the scene for a menu.
	/// </summary>
	std::vector<IDrawable*> _objVect;

public:

	Scene();
	~Scene();

	/// <summary>
	/// Adds an object to the back of to the scene object vector.
	/// </summary>
	/// <param name="object">The object to add to the vector.</param>
	virtual void addObject(IDrawable* object);

	virtual void removeObject(IDrawable* object);

	std::vector<IDrawable*> getObjectMap();

};

