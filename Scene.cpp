#include "Scene.h"
#include "easylogging++.h"
#include <algorithm>

Scene::Scene() :
	_menuVect({})
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
	_menuVect.push_back(std::pair<GameObject*, SDL_Texture*>(object, texture));
}

void Scene::removeObject(GameObject* object, SDL_Texture* texture)
{
	//_sceneMap.erase(object->getZ());
	
	// Find the element
	std::vector<std::pair<GameObject*, SDL_Texture*>>::iterator itr;
	itr = std::find(_menuVect.begin(), _menuVect.end(), std::pair<GameObject*, SDL_Texture*>(object, texture));
	if (itr != _menuVect.end())
	{
		_menuVect.erase(itr);
	}
	else
	{
		LOG(INFO) << "Scene object not found! Object not removed from scene vector.";
	}

}

std::vector<std::pair<GameObject*, SDL_Texture*>> Scene::getObjectMap()
{
	return _menuVect;
}