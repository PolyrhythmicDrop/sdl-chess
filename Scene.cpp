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

void Scene::addObject(GameObject* object, SDL_Texture* texture)
{
	// _textureMap.insert(std::pair<GameObject*, SDL_Texture*>(object, texture));
	//_sceneMap.insert({object->getZ(), std::pair<GameObject*, SDL_Texture*>(object, texture) });
	_objVect.push_back(std::pair<GameObject*, SDL_Texture*>(object, texture));
}

void Scene::removeObject(GameObject* object, SDL_Texture* texture)
{
	//_sceneMap.erase(object->getZ());
	
	// Find the element
	std::vector<std::pair<GameObject*, SDL_Texture*>>::iterator itr;
	itr = std::find(_objVect.begin(), _objVect.end(), std::pair<GameObject*, SDL_Texture*>(object, texture));
	if (itr != _objVect.end())
	{
		_objVect.erase(itr);
	}
	else
	{
		LOG(INFO) << "Scene object not found! Object not removed from scene vector.";
	}

}

std::vector<std::pair<GameObject*, SDL_Texture*>> Scene::getObjectMap()
{
	return _objVect;
}