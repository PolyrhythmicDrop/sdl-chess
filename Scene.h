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

	/// <summary>
	/// Vector containing all the draw functions of the objects in the scene, in the order that they are to be drawn.
	/// </summary>
	std::vector<std::function<void(int, int, int, int)>> _sceneDrawVector;

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

	/// <summary>
	/// Add draw functions to the scene draw vector.
	/// </summary>
	/// <param name="object">The object whose draw function will be added.</param>
	virtual void addToSceneDrawVector(IDrawable* object, std::function<void(int, int, int, int)> drawFunction);
};

