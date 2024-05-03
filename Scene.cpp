#include "Scene.h"

Scene::Scene() :
	_objectVector({})
{
	std::cout << "Scene created!";
}

Scene::~Scene()
{
	std::cout << "Scene destructed!";
}

void Scene::addObject(GameObject* object)
{
	_objectVector.push_back(object);
}

const std::vector<GameObject*> Scene::getObjectVector()
{
	return _objectVector;
}

void Scene::addToSceneDrawVector(IDrawable* object, std::function<void(int, int, int, int)> drawFunction)
{
	_sceneDrawVector.push_back(drawFunction);
}