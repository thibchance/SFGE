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


#ifndef SFGE_GAMEOBJECT_H
#define SFGE_GAMEOBJECT_H

#include <utility/json_utility.h>
#include <engine/engine.h>
//External includes
#include <SFML/System.hpp>
//STL includes
#include <list>
#include <string>

namespace sfge
{
class Component;
class Transform;
class Collider;

/**
* \brief The basic Game Object handler containing a list of Components
* it always contains a Transform component
*/
class GameObject
{
public:
	GameObject();
	~GameObject();
	/**
	* \brief Update the GameObject and its Components
	* \param dt Delta time since last frame
	*/
	void Update(sf::Time dt);
	/**
	* \brief Load a GameObject and create all its Component
	* \param gameObjectJson the sub json associated with the Game Object
	* \return the heap GameObject that will need to be destroyed
	*/
	static GameObject* LoadGameObject(Engine& engine, json& gameObjectJson);
	/**
	 * \brief Get the Transform attached to the GameObject
	 * \return Pointer to Transform
	 */
	Transform* GetTransform();

	void SetTransform(Transform* transform);

	/**
	 * \brief Get The Component of type given the T by template
	 * \return Return the first Component of type T that is attached to the GameObject
	 */
	template <class T>
	T* GetComponent()
	{
		for (auto component : m_Components)
		{
			auto castComponent = dynamic_cast<T*>(component);
			if (castComponent != nullptr)
			{
				return castComponent;
			}
		}
		return nullptr;
	}

	template<> Component* GetComponent<Component>();

	/**
	* \brief Return the reference to all the Component in the GameObject
	*/
	std::list<Component*>& GetComponents();

	/**
	 * \brief Get the name of the GameObject in the Scene
	 * \return Return the const reference of the string name
	 */
	const std::string& GetName();

	void SetName(std::string name);

	void OnTriggerEnter(Collider* collider);
	void OnCollisionEnter(Collider* collider);

protected:
	friend class Component;
	std::list<Component*> m_Components;
	std::string m_Name = "";
	Transform* m_Transform = nullptr;
};
}
#endif
