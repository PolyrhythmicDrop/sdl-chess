#include "Scene.h"

Scene::Scene()
{

}

Scene::~Scene()
{

}

void Scene::addObject(GameObject* object)
{
	_objectVector.push_back(object);
}

void Scene::addToSceneDrawVector(IDrawable* object, std::function<void(int, int, int, int)> drawFunction)
{
	_sceneDrawVector.push_back(drawFunction);
}