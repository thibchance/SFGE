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

#include <engine/component.h>
#include <engine/transform.h>
#include <graphics/sprite.h>
#include <graphics/shape.h>
#include <python/pycomponent.h>
#include <engine/log.h>

namespace sfge
{

Component::Component(GameObject* gameObject) :
	gameObject(gameObject)
{

}

Component* Component::LoadComponent(Engine& engine, json& componentJson, GameObject* gameObject)
{
	Component* component = nullptr;
	if(CheckJsonParameter(componentJson, "name", json::value_t::string))
	{
		std::ostringstream oss;
		oss << "Loading component: "<<componentJson["name"];
		Log::GetInstance()->Msg(oss.str());
	}
	if (CheckJsonNumber(componentJson, "type"))
	{
		ComponentType componentType = (ComponentType)componentJson["type"];

		switch(componentType)
		{
		case ComponentType::TRANSFORM:
			gameObject->SetTransform(Transform::LoadTransform(componentJson, gameObject));
			component = gameObject->GetTransform();
			break;
		case ComponentType::SPRITE:
			component = Sprite::LoadSprite(engine, componentJson, gameObject);
			break;
		case ComponentType::PYCOMPONENT:
			component = PyComponent::LoadPythonScript(engine, componentJson, gameObject);
			break;
		case ComponentType::SHAPE:
			component = Shape::LoadShape(engine, componentJson, gameObject);
			break;
		default:
			break;
		}
		if (component != nullptr)
		{
			component->Init();
			gameObject->m_Components.push_back(component);
		}
		else
		{
			Log::GetInstance()->Error("Undefined type for component");
		}
	}
	else
	{
		Log::GetInstance()->Error("No type defined for component");
	}
	return component;
}

GameObject* Component::GetGameObject()
{
	return gameObject;
}

}
