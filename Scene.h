#pragma once
#include "GameObject.h"
#include <map>

/// <summary>
/// Abstract class for building scenes.
/// </summary>
class Scene
{
protected:

	/// <summary>
	/// Map containing all the objects in the scene, plus their associated textures.
	/// </summary>
	std::map<int, std::pair<GameObject*, SDL_Texture*>> _sceneMap;

public:

	Scene();
	~Scene();

	/// <summary>
	/// Build the scene up by adding objects and constructing the draw vector with those objects.
	/// </summary>
	/// <returns></returns>
	virtual void buildMenu() = 0;

	/// <summary>
	/// Adds an object to the back of to the scene object vector.
	/// </summary>
	/// <param name="object">The object to add to the vector.</param>
	virtual void addObject(GameObject* object, SDL_Texture* texture);

	const std::map<int, std::pair<GameObject*, SDL_Texture*>> getObjectMap();

};

