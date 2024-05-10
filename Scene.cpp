#include "Scene.h"
#include "easylogging++.h"

Scene::Scene() :
	_sceneMap({})
{
	LOG(INFO) << "Scene created!\n";
}

Scene::~Scene()
{
	LOG(INFO) << "Scene destructed!\n";
}

void Scene::addObject(GameObject* object, SDL_Texture* texture)
{
	// _textureMap.insert(std::pair<GameObject*, SDL_Texture*>(object, texture));

	_sceneMap.insert({object->getZ(), std::pair<GameObject*, SDL_Texture*>(object, texture) });
}

void Scene::removeObject(GameObject* object)
{
	_sceneMap.erase(object->getZ());
}

const std::map<int, std::pair<GameObject*, SDL_Texture*>> Scene::getObjectMap()
{
	return _sceneMap;
}