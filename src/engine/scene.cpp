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
#include <fstream>
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
	std::list<std::string>& scenesList = Engine::GetInstance()->GetConfig()->scenesList;
	if(scenesList.size() > 0)
	{
		fs::path firstScenePath = *scenesList.begin();
		if (fs::is_regular_file(firstScenePath))
		{
			if (firstScenePath.extension() == fs::path(".scene"))
			{
				currentScene = LoadScene(firstScenePath.c_str());
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

Scene* SceneManager::LoadScene(std::string sceneName)
{
	std::ifstream sceneFile(sceneName.c_str());
	if (sceneFile.peek() == std::ifstream::traits_type::eof())
	{
		Log::GetInstance()->Error("EMPTY SCENE FILE");
		return nullptr;
	}
	json sceneJson;
	try
	{
		sceneFile >> sceneJson;
	}
	catch (json::parse_error& e)
	{
		Log::GetInstance()->Error("THE SCENE FILE IS NOT JSON");
		return nullptr;
	}
	Scene* scene = new Scene();
	scene->name = sceneJson["name"];
	for(json gameObjectJson : sceneJson["gameObjects"])
	{
		GameObject* gameObject = GameObject::LoadGameObject(gameObjectJson);
		if(gameObject)
		{
			scene->m_GameObjects.push_back(gameObject);
		}
	}
	return scene;
}



void SceneManager::Destroy()
{
	if(currentScene)
	{
		delete currentScene;
		currentScene = nullptr;
	}
}

void Scene::Update(sf::Time dt)
{
	for(GameObject* gameObject : m_GameObjects)
	{
		gameObject->Update(dt);
	}
}

Scene::~Scene()
{
	while(!m_GameObjects.empty())
	{
		delete m_GameObjects.front();
		m_GameObjects.pop_front();
	}
}
}
