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
#include <graphics/sprite.h>

namespace sfge
{
void GameObject::Update(sf::Time dt)
{
	for(Component* component : m_Components)
	{
		component->Update(dt);
	}
}

GameObject* GameObject::LoadGameObject(json gameObjectJson)
{
	GameObject* gameObject = new GameObject();
	gameObject->name = gameObjectJson["name"];
	for(json componentJson : gameObjectJson["components"])
	{
		Component* component = nullptr;
		std::string componentType = componentJson["type"];
		if(componentType == "Transform")
		{
			component = Transform::LoadTransform(componentJson);
		}
		else if(componentType == "Sprite")
		{
			component = Sprite::LoadSprite(componentJson);
		}
		if(component)
		{
			gameObject->m_Components.push_back(component);
		}
	}
	return gameObject;
}
}
