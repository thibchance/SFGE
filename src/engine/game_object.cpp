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

#include <engine/game_object.h>
#include <engine/component.h>
#include <engine/transform.h>
#include <engine/log.h>
#include <python/pycomponent.h>
#include <python/python_engine.h>

#include <memory>

namespace sfge
{
void GameObject::Update(sf::Time dt)
{
	for(auto component : m_Components)
	{
		if(component == nullptr)
		{
			Log::GetInstance()->Error("Component in GameObject is null");
			continue;
		}
		component->Update(dt.asSeconds());
	}
}

std::shared_ptr<GameObject> GameObject::LoadGameObject(Engine& engine, json& gameObjectJson)
{
	std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>();
	if (CheckJsonParameter(gameObjectJson, "name", json::value_t::string))
	{
		gameObject->m_Name = gameObjectJson["name"].get<std::string>();
	}
	else
	{
		gameObject->m_Name = "GameObject";
	}

	{
		std::ostringstream oss;
		oss << "Loading game_object: " << gameObject->m_Name;
		Log::GetInstance()->Msg(oss.str());
	}

	if (CheckJsonParameter(gameObjectJson, "components", json::value_t::array))
	{
		for (json& componentJson : gameObjectJson["components"])
		{
			auto newComponent = Component::LoadComponent(engine, componentJson, *gameObject);
			if(newComponent != nullptr)
			{
				gameObject->m_Components.push_back(newComponent);
			}
			else
			{
				std::ostringstream oss;
				oss << "Component from: " << componentJson << " is nullptr";
				Log::GetInstance()->Error(oss.str());
			}
		}
	}

	//if there is no transform, it is always at the beginning of the list
	if(gameObject->m_Transform == nullptr)
	{
		auto transform = new Transform(*gameObject);
		gameObject->m_Components.push_front(transform);
		gameObject->m_Transform = transform;
	}
	return gameObject;
}

Transform* GameObject::GetTransform()
{
	return m_Transform;
}

void GameObject::SetTransform(Transform* transform)
{
	m_Transform = transform;
}
template <typename T>
T* GameObject::GetComponent()
{
	for(auto component : m_Components)
	{
		auto castComponent = std::dynamic_pointer_cast<T>(component);
		if(castComponent != nullptr)
		{
			return castComponent;
		}
	}
	return nullptr;
}

GameObject::~GameObject()
{
	/*for(auto c_itr = m_Components.begin(); c_itr != m_Components.end(); c_itr++)
	{
		if(dynamic_cast<PyComponent*>((*c_itr)) != nullptr)
		{

		}
		else
		{
			delete(*c_itr);
		}
	}*/
	Log::GetInstance()->Error("DESTROY GAME OBJECT");
}

const std::string & GameObject::GetName()
{
	return m_Name;
}

}
