#pragma once
#include <vector>
#include "Decoration.h"
#include "Button.h"
#include <functional>
#include <vector>

/// <summary>
/// Abstract class for building scenes.
/// </summary>
class Scene
{
protected:

	
	/// <summary>
	/// Vector containing all the objects in the scene.
	/// </summary>
	std::vector<GameObject*> _objectVector;

public:

	Scene();
	~Scene();

	/// <summary>
	/// Build the scene up by adding objects and constructing the draw vector with those objects.
	/// </summary>
	/// <returns></returns>
	virtual void buildScene() = 0;

	/// <summary>
	/// Adds an object to the back of to the scene object vector.
	/// </summary>
	/// <param name="object">The object to add to the vector.</param>
	virtual void addObject(GameObject* object);

	const std::vector<GameObject*> getObjectVector();

};

