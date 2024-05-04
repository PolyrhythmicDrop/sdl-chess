#include "Scene.h"

Scene::Scene() :
	_sceneMap({})
{
	std::cout << "Scene created!";
}

Scene::~Scene()
{
	std::cout << "Scene destructed!";
}

void Scene::addObject(GameObject* object, SDL_Texture* texture)
{
	_sceneMap.insert({ object, texture });
}

const std::map<GameObject*, SDL_Texture*> Scene::getObjectMap()
{
	return _sceneMap;
}