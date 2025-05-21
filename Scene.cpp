#include "Scene.h"
#include "easylogging++.h"
#include <algorithm>

Scene::Scene() :
	_objVect({})
{
	LOG(INFO) << "Scene created!";
}

Scene::~Scene()
{
	LOG(INFO) << "Scene destructed!";
}

void Scene::addObject(IDrawable* object)
{
	// _textureMap.insert(std::pair<GameObject*, SDL_Texture*>(object, texture));
	//_sceneMap.insert({object->getZ(), std::pair<GameObject*, SDL_Texture*>(object, texture) });
	_objVect.push_back(object);
}

void Scene::removeObject(IDrawable* object)
{
	
	// Find the element
	std::vector<IDrawable*>::iterator itr;
	itr = std::find(_objVect.begin(), _objVect.end(), object);
	if (itr != _objVect.end())
	{
		_objVect.erase(itr);
	}
	else
	{
		LOG(INFO) << "Scene object not found! Object not removed from scene vector.";
	}

}

std::vector<IDrawable*> Scene::getObjectMap()
{
	return _objVect;
}