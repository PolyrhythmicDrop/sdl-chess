#include "Scene.h"

Scene::Scene() :
	_sceneMap({})
{
	std::cout << "Scene created!\n";
}

Scene::~Scene()
{
	std::cout << "Scene destructed!\n";
}

void Scene::addObject(GameObject* object, SDL_Texture* texture)
{
	_sceneMap.insert(std::pair<GameObject*, SDL_Texture*>(object, texture));
}

const std::map<GameObject*, SDL_Texture*> Scene::getObjectMap()
{
	return _sceneMap;
}