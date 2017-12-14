/*
 MIT License
 
 Copyright (c) 2017 SAE Institute Switzerland AG
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */
//Externals includes
#include "json.hpp"
using json = nlohmann::json;
//STL includes
#include <experimental/filesystem>
//SFGE includes
#include <engine/game_object.h>
#include <engine/scene.h>
#include <engine/log.h>

// for convenience
namespace fs = std::experimental::filesystem;


namespace sfge
{

void SceneManager::Init()
{
	std::list<std::string>& scenesList = m_Engine.GetConfig()->scenesList;
	if(scenesList.size() > 0)
	{
		const fs::path firstScenePath = *scenesList.begin();
		if (fs::is_regular_file(firstScenePath))
		{
			if (firstScenePath.extension() == fs::path(".scene"))
			{
				currentScene = LoadScene(firstScenePath.string());
			}
		}
	}
}



void SceneManager::Update(sf::Time dt)
{
	if(currentScene)
	{
		currentScene->Update(dt);
	}
}

std::shared_ptr<Scene> SceneManager::LoadScene(std::string sceneName)
{
	auto sceneJsonPtr = LoadJson(sceneName);
	json sceneJson = *sceneJsonPtr;
	if(sceneJson == nullptr)
	{
		return nullptr;
	}
	std::shared_ptr<Scene> scene = std::make_shared<Scene>();
	scene->name = sceneJson["name"].get<std::string>();
	for(json gameObjectJson : sceneJson["gameObjects"])
	{
		std::shared_ptr<GameObject> gameObject = GameObject::LoadGameObject(gameObjectJson);
		if(gameObject)
		{
			scene->m_GameObjects.push_back(gameObject);
		}
	}
	return scene;
}



void SceneManager::Destroy()
{
}

void Scene::Update(sf::Time dt)
{
	for(auto gameObject : m_GameObjects)
	{
		gameObject->Update(dt);
	}
}

Scene::~Scene()
{
	while(!m_GameObjects.empty())
	{
		m_GameObjects.pop_front();
	}
}
}
